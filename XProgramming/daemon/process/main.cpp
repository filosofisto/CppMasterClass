#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

const unsigned int BD_MAX_CLOSE = 8192;

void info(const string& message)
{
    syslog(LOG_INFO, "%s", message.c_str());
}

void warn(const string& message)
{
    syslog(LOG_WARNING, "%s", message.c_str());
}

void error(const string& message)
{
    syslog(LOG_ERR, "%s", message.c_str());
}

void executeCycle()
{
    info("Doing something interesting...");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    info("Done!");
}

void start_as_daemon()
{
  // become background process
  switch (fork()) {
    case -1: {
        cerr << "Fork failed" << endl; 
        _exit(EXIT_FAILURE);
    }
    case 0: {
        // Child process
        int childPid = getpid();

        cout << endl;
        cout << "[" << childPid << "] " << "Child process created with success\n";
        cout << "[" << childPid << "] " << "Monitoring expensive processes...";

        // become leader of new session
        if (setsid() == -1) {
            _exit(EXIT_FAILURE);
        }

        switch (fork()) {
            case -1: _exit(EXIT_FAILURE);
            case 0: {
                int monitorPid = getpid();
                cout << endl;
                cout << "[" << monitorPid << "] " << "Monitor created with success, PID: " << monitorPid << endl;

                // Clear file mode creation mask
                umask(0);

                // Change to root directory
                chdir("/");

                // Close all open files
                int maxfd = sysconf(_SC_OPEN_MAX);
                if (maxfd == -1) {
                    maxfd = BD_MAX_CLOSE;
                }

                for (int fd{0}; fd < maxfd; ++fd) {
                    close(fd);
                }               

                // Reopen standard file descriptors to /dev/null
                close(STDIN_FILENO);

                int fd = open("/dev/null", O_RDWR);

                if (fd != STDIN_FILENO) {
                    _exit(EXIT_FAILURE);
                } 
                if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO) {
                    _exit(EXIT_FAILURE);
                }
                if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO) {
                    _exit(EXIT_FAILURE);
                }

                // init logging
                openlog("Daemon Monitor", LOG_PID | LOG_CONS, LOG_USER);

                for (;;) {
                    // here is the task (finally)
                    executeCycle();

                    // wait sometime to execute again
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }

                closelog();
            }
            default: _exit(EXIT_SUCCESS);
        }

        _exit(EXIT_SUCCESS);
    }
    default: {
        int parentPid = getpid();
        // Parent process
        cout << "[" << parentPid << "] " << "----------------------------------------------------\n";
        cout << "[" << parentPid << "] " << "Daemon Sample\n";
        cout << "[" << parentPid << "] " << "----------------------------------------------------\n";
        cout << "[" << parentPid << "] " << "Parent PID: " << parentPid << "\n";
        cout << "[" << parentPid << "] " << "Child process created with success\n";
        cout << "[" << parentPid << "] " << "Finishing parent process, bye :)" << endl;
        _exit(EXIT_SUCCESS);
    }
  }
}

int main()
{
    start_as_daemon();
 
    return EXIT_SUCCESS;
}
