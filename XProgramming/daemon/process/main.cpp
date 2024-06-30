#include <iostream>
#include "process_stat.h"

int main(int argc, char** argv)
{
	ProcessStat pstat;
	pstat.readStat();

	std::cout << "List of Processing running\n";
	for (const auto& process: pstat.getProcesses()) {
		std::cout << process.pid << " " << process.name << " " << process.utime << " " << process.stime << "\n";
	}

	return EXIT_SUCCESS;
}

