#ifndef __PROCESS_STAT_H__
#define __PROCESS_STAT_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <dirent.h>
#include <unistd.h>

typedef struct ProcessInfo {
    int pid;
    std::string name;
    long utime;
    long stime;
} PInfo;

class ProcessStat
{
public:

  ProcessStat() = default;
  virtual ~ProcessStat() = default;

  ProcessStat(const ProcessStat&) = delete;
  ProcessStat(ProcessStat&&) = delete;

  ProcessStat& operator=(const ProcessStat&) = delete;
  ProcessStat& operator=(ProcessStat&&) = delete;

  void readStat();
  std::vector<PInfo> getProcesses() const;

private:
  void readProcesses();
  long getSystemUptime();
  long getTotalCPUUsage(); 

  std::vector<PInfo> processes; 
};

#endif
