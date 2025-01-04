#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sys/stat.h>       // required by umask
#include <fcntl.h>          // required by open
#include <syslog.h>         // required by openlog, closelog, syslog

using std::cout;
using std::cerr;
using std::endl;
using std::string;

void info(const string& message)
{
    syslog(LOG_INFO, "%s", message.c_str());
}

void do_work()
{
    info("Doing something interesting...");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    info("Done!");
}

int main(int argc, char** argv)
{
    switch (fork()) {
        case -1:
            cerr << "Fork failed!" << endl;
            _exit(EXIT_FAILURE);
        case  0: {
            // child running in background
            pid_t pc = getpid();
            cout << "[" << pc << "] - Parent Child\n";
           
            // create new session
            if (setsid() == -1) {
                _exit(EXIT_FAILURE);
            }

            switch (fork()) {
                case -1: 
                case  0: {
                    // Daemon
                    pid_t pd = getpid();
                    cout << "[" << pd << "] - Daemon Process\n";

                    umask(0);

                    chdir("/");

                    int maxfd = sysconf(_SC_OPEN_MAX);
                    if (maxfd == -1) {
                        maxfd = 8196;
                    }

                    for (int fd{0}; fd < maxfd; ++fd) {
                        close(fd);
                    }

                    int fd_dev_null = open("/dev/null", O_RDWR);

                    if (fd_dev_null != STDIN_FILENO) {
                        _exit(EXIT_FAILURE);
                    }
                    if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO) {
                        _exit(EXIT_FAILURE);
                    }
                    if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO) {
                        _exit(EXIT_FAILURE);
                    }

                    // Daemon Work
                    openlog("MyDaemon", LOG_PID, LOG_USER);

                    for(;;) {
                        do_work();

                        std::this_thread::sleep_for(std::chrono::seconds(3));
                    }

                    closelog();

                    _exit(EXIT_SUCCESS);
                }
                default: {
                    cout << "[" << pc << "] - New session created" << endl;
                    _exit(EXIT_SUCCESS);
                }
            }

            _exit(EXIT_SUCCESS);
        }
        default: {
            // parent
            pid_t pp = getpid();

            cout << "[" << pp << "] - Parent Process\n";
            cout << "[" << pp << "] - Bye!" << endl;
            _exit(EXIT_SUCCESS);
        }
    }

    return EXIT_SUCCESS;
}
