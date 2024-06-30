#include "process_stat.h"

std::vector<PInfo> ProcessStat::getProcesses() const
{
	return processes;
}

void ProcessStat::readProcesses()
{
  processes.clear();

  struct dirent *entry;
  DIR *dp = opendir("/proc");

  if (dp == nullptr) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dp))) {
    int pid = atoi(entry->d_name);
    if (pid > 0) {
      PInfo pInfo;
      pInfo.pid = pid;

      std::stringstream stat_path;
      stat_path << "/proc/" << pid << "/stat";
      std::ifstream stat_file(stat_path.str());

      if (stat_file) {
        std::string line;
        getline(stat_file, line);
        std::stringstream stat_stream(line);

        std::string comm;
        char state;
        long int utime, stime;
        stat_stream >> pInfo.pid >> comm >> state;

        for (int i = 0; i < 11; ++i) {
          stat_stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        }

        stat_stream >> utime >> stime;
        pInfo.name = comm.substr(1, comm.length()-2);
        pInfo.utime = utime;
        pInfo.stime = stime;

        processes.push_back(pInfo);
      }
    }
  }

  closedir(dp);
}

long ProcessStat::getSystemUptime() {
    std::ifstream uptime_file("/proc/uptime");
    double uptime;
    uptime_file >> uptime;
    return static_cast<long>(uptime);
}

long ProcessStat::getTotalCPUUsage()
{
  std::ifstream stat_file("/proc/stat");
  std::string line;
  getline(stat_file, line);
  std::stringstream stat_stream(line);

  std::string cpu;
  long user, nice, system, idle, iowait, irq, softirq;
  stat_stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

  return user + nice + system + idle + iowait + irq + softirq;
}

void ProcessStat::readStat()
{
	readProcesses();
}
