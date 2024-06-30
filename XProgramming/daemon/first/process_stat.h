#ifndef __PROCESS_STAT_H__
#define __PROCESS_STAT_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>

class ProcessStat
{
public:

  ProcessStat() = default;
  virtual ~ProcessStat() = default;

  ProcessStat(const ProcessStat&) = delete;
  ProcessStat(ProcessStat&&) = delete;

  ProcessStat& operator=(const ProcessStat&) = delete;
  ProcessStat& operator=(ProcessStat&&) = delete;

  struct ProcessInfo {
    int pid;
    std::string name;
    long utime;
    long stime;
  };

  void readStat();

private:
  void readProcesses();
  long getSystemUptime();
  long getTotalCPUUsage();
  

  std::vector<ProcessInfo> processes; 
};

#endif
