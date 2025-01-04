#include <iostream>
#include <fmt/core.h>
#include <signal.h>

using std::cout, std::endl, std::cerr, std::atoi, fmt::print;

void usage(char** argv)
{
    print("Usage: {} [pid] [sig]\n", argv[0]);
    print("\t[pid]: Process Id to receive the signal\n");
    print("\t[sig]: Signal to be sent to process\n");
    print("\t\t0: Used to check if process exists\n");
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        usage(argv);
        return EXIT_FAILURE;
    }

    int pid = atoi(argv[1]);
    int sig = atoi(argv[2]);

    int result = kill(pid, sig);

    if (sig == 0) {
        if (result == 0) {
            print("Process {} exists, we can send signals to it\n", pid);
        } else {
            switch (errno) {
                case EPERM:
                    print("Process {} exists but we do not have permition to send it a signal\n", pid);
                    break;
                case ESRCH:
                    print("Process {} does not exists\n", pid);
                    break;
                default:
                    print("Error on kill call: {}\n", errno);
            }
        }
    } else {
        if (result == -1) {
            print("Error on kill call: {}\n", errno);
        } else {
            print("Success on send signal {} to process {}\n", sig, pid);
        }
    }

    return EXIT_SUCCESS;
}
