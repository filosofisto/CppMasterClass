#ifndef __CPU_USAGE__
#define __CPU_USAGE__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>


struct ProcessInfo {
    int pid;
    std::string name;
    long utime;
    long stime;
};

long getSystemUptime() {
    std::ifstream uptime_file("/proc/uptime");
    double uptime;
    uptime_file >> uptime;
    return static_cast<long>(uptime);
}

std::vector readProcesses()
{
  std::vector<ProcessInfo> processes;
  struct dirent *entry;
  DIR *dp = opendir("/proc");

  if (dp == nullptr) {
    perror("opendir");
    return processes;
  }

  while ((entry = readdir(dp))) {
    int pid = atoi(entry->d_name);
    if (pid > 0) {
      ProcessInfo pInfo;
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

  return processes;
}

long getTotalCPUUsage()
{
  std::ifstream stat_file("/proc/stat");
  std::string line;
  getline(stat_file, line);
  std::stringstream stream_stat(line);

  std::string cpu;
  long user, nice, system, idle, iowait, irq, softirq;
  stat_stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

  return user + nice + system + idle + iowait + irq + softirq;
}

void verify()
{

}

#endif
