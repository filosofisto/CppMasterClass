#include "process_stat.h"

using std::string;
using std::vector;
using std::stringstream;
using std::ifstream;
using std::pair;
using std::optional;
using std::nullopt;
using std::regex;

ProcessStat::ProcessStat(): lastTotalCPUTime{0}
{

}

void ProcessStat::initProcesses()
{
    processes.clear();

    struct dirent *entry;
    DIR *dp = opendir("/proc");

    if (dp == nullptr) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (!isInteger(string(entry->d_name))) {
            continue;
        }

        pid_t pid = static_cast<pid_t>(atoi(entry->d_name));
        
        if (pid > 0) {
            PInfo pInfo;
            pInfo.pid = pid;

            stringstream stat_path;
            stat_path << "/proc/" << pid << "/stat";
            ifstream stat_file(stat_path.str());

            if (stat_file) {
                string line;
                getline(stat_file, line);
                stringstream stat_stream(line);
                vector<std::string> parts;
                string token;
                string comm;
                unsigned long utime, stime;

                while (stat_stream >> token) {
                    parts.push_back(token);
                }

                comm = parts[1];
                comm = comm.substr(1, comm.size()-2);
                utime = stoi(parts[13]);
                stime = stoi(parts[14]);                

                pInfo.utime1 = utime;
                pInfo.stime1 = stime;
                pInfo.processTime = -1;
                pInfo.cpuUsage = 0.0f;

                processes.push_back(pInfo);
            }
        }
    }

    closedir(dp);
}

pair<unsigned long, unsigned long> ProcessStat::readTimes(pid_t pid) const
{
    string filename{"/proc/" + std::to_string(pid) + "/stat"};
    ifstream file{filename};
    string line;
    getline(file, line);
    stringstream stat_stream(line);
    vector<std::string> parts;
    string token; 
    long int utime, stime;

    while (stat_stream >> token) {
        parts.push_back(token);
    }

    utime = stoi(parts[13]);
    stime = stoi(parts[14]);

    return pair<unsigned long, unsigned long>{utime, stime};
}

void ProcessStat::readProcessStats(pid_t pid)
{
    auto[utime, stime] = readTimes(pid);

    auto it = find_if(processes.begin(), processes.end(), [pid](const ProcessInfo& process) {
        return process.pid == pid;
    });

    if (it != processes.end()) {
        it->utime2 = utime;
        it->stime2 = stime;

        if ((it->utime2 + it->stime2) > (it->utime1 + it->stime1)) {
            it->processTime = (it->utime2 + it->stime2) - (it->utime1 + it->stime1);
        } else {
            it->processTime = 0;
        }
    }
}

unsigned long ProcessStat::getSystemUptime() {
    ifstream uptime_file("/proc/uptime");
    double uptime;
    uptime_file >> uptime;
    return static_cast<long>(uptime);
}

unsigned long ProcessStat::getTotalCPUTime()
{
  ifstream stat_file("/proc/stat");
  string line;
  getline(stat_file, line);
  stringstream stat_stream(line);

  string cpu;
  long user, nice, system, idle, iowait, irq, softirq;
  stat_stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

  return user + nice + system + idle + iowait + irq + softirq;
}

void ProcessStat::readStat()
{
    unsigned long totalCPU1 = getTotalCPUTime();
	initProcesses();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    readAllProcessesStats();

    unsigned long totalCPU2 = getTotalCPUTime();

    lastTotalCPUTime = totalCPU2 - totalCPU1;
    updateProcessesCPUUsage();

    cleanInvalidValues();
    sortDescByCPUUsage();
}

void ProcessStat::sortDescByCPUUsage()
{
    sort(processes.begin(), processes.end(), [](const ProcessInfo& pa, const ProcessInfo& pb) {
        return pb.cpuUsage < pa.cpuUsage;
    });
}

optional<ProcessInfo> ProcessStat::theHeaviestProcess() const
{
    if (!processes.empty()) {
        return processes.front();
    }

    return nullopt; 
}

void ProcessStat::readAllProcessesStats()
{
    for (const auto& process: processes) {
        readProcessStats(process.pid);
    }
}

void ProcessStat::updateProcessesCPUUsage()
{
    for (auto& process: processes) {
        process.cpuUsage = 100.0 * process.processTime / lastTotalCPUTime;
    }
}

void ProcessStat::cleanInvalidValues()
{
    processes.erase(remove_if(processes.begin(), processes.end(), [](ProcessInfo p) {
        return p.processTime == 0;
    }));
}

bool ProcessStat::isInteger(const string& text) const
{
  regex intPattern("^-?\\d+$");
  return regex_match(text, intPattern);
}

unsigned int ProcessStat::getLastTotalCPUTime() const
{
    return lastTotalCPUTime;
}
