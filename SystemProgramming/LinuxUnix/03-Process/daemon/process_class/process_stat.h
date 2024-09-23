#ifndef __PROCESS_STAT_H__
#define __PROCESS_STAT_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <regex>
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#include <optional>
#include <thread>
#include <chrono>

typedef struct ProcessInfo {
    pid_t pid;
    std::string name;
    unsigned long utime1; // utime: Amount of time the process has been scheduled in user mode
    unsigned long stime1; // stime: Amount of time the process has been scheduled in kernel mode
    unsigned long utime2;
    unsigned long stime2;
    unsigned long processTime;
    float cpuUsage;
} PInfo;

class ProcessStat
{
public:
    ProcessStat();
    virtual ~ProcessStat() = default;

    ProcessStat(const ProcessStat&) = delete;
    ProcessStat(ProcessStat&&) = delete;

    ProcessStat& operator=(const ProcessStat&) = delete;
    ProcessStat& operator=(ProcessStat&&) = delete;

    void readStat();
    unsigned int getLastTotalCPUTime() const;
    std::optional<ProcessInfo> theHeaviestProcess() const;
private:
    void initProcesses();
    unsigned long getSystemUptime();
    unsigned long getTotalCPUTime();
    void readProcessStats(pid_t pid);
    void readAllProcessesStats();
    void updateProcessesCPUUsage();
    void sortDescByCPUUsage();
    bool isInteger(const std::string& text) const; 
    void cleanInvalidValues();
    std::pair<unsigned long, unsigned long> readTimes(pid_t pid) const;

    std::vector<PInfo> processes;
    unsigned int lastTotalCPUTime; 
};

#endif
