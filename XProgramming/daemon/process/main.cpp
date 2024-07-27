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
    // 1. Become background process
    //    - Assuming the parent has been started from terminal, when it finishes another shell prompt is showed
    //      and child continues to run in background
    //    - The child process is guaranteed not to be a process group leader, since it inherited its process group ID 
    //      from its parent and obtained its own unique process ID, which differs from the inherited process group ID.
    //      This is required in order to be able to successfully perform the next step
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

            // 2. Start a new session and free itself of any association with a controlling terminal
            if (setsid() == -1) {
                _exit(EXIT_FAILURE);
            }

            // 3. Ensure that the device does not become the controlling terminal 
            //    If the daemon never opens any terminal device thereafter, then we do not need to worry about the daemon
            //    reacquiring a controlling terminal. If the daemon might later open a terminal device, then we must take
            //    steps to ensure that the device does not become the controlling terminal
            //    A simple way to do that is do another fork() after setsid() call, let parent exit and child continue. This
            //    ensure that child is not the session leader, and thus, according to the System V conventions for the acquisition
            //    of a controlling terminal, the process can never reacquire a controlling terminal
            switch (fork()) {
                case -1: _exit(EXIT_FAILURE);
                case 0: {
                    int monitorPid = getpid();
                    cout << endl;
                    cout << "[" << monitorPid << "] " << "Monitor created with success, PID: " << monitorPid << endl;

                    // 4. Clear file mode creation mask
                    //    Ensure that, when the daemon creates files and directories, they have the requested permissions
                    umask(0);

                    // 5. Change to root directory
                    //    Because normally the daemon run until the system shutdown, and running in another than the one 
                    //    containing /, then the filesystem cannot be unmounted.
                    //    Alternativally the daemon can set its folder where it never need to be unmounted.
                    chdir("/");

                    // 6. Close all open files inherited from its parent
                    //    Because the daemon does not need of terminal does not make sense keep file descriptors 0, 1, and 2.
                    //    Futhermore, we cannot unmount any file systems on which the long-lived daemon holds files open.
                    //    And, as usual, we should close unused open file descriptors because file descriptors are a finite
                    //    resource
                    int maxfd = sysconf(_SC_OPEN_MAX);
                    if (maxfd == -1) {
                        maxfd = BD_MAX_CLOSE;
                    }

                    for (int fd{0}; fd < maxfd; ++fd) {
                        close(fd);
                    }               

                    // 7. Redirect all iteraction with file descriptors 0, 1 and 2 to /dev/null
                    //    It ensures that if the daemon calls library functions that perform I/O on these descriptors, those 
                    //    functions will not unexpectedly fail
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
