#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <thread>
#include <chrono>

using std::cout, std::endl, std::cerr;
using std::this_thread::sleep_for, std::chrono::seconds;

static void signal_handler(int sig)
{
    static size_t count{0};

    if (sig == SIGINT) {
        cout << "\nPressed Ctrl+C " << (++count) << '\n';
        return; 
    }
    cout << "Ctrl+\\ (SIGQUIT) pressed! Bye!\n";
    _exit(EXIT_SUCCESS);
}

void install_signal_handler(int sig)
{
    if (signal(sig, signal_handler) == SIG_ERR) {
        cerr << "Error to install the signal handler for " << sig << '\n';
        abort();
    }
}

int main()
{
    cout << "PID: " << getpid() << '\n';

    install_signal_handler(SIGINT);
    install_signal_handler(SIGQUIT);

    for (int i{0}; ; ++i) {
        cout << "Waiting " << i << '\n';
        sleep_for(seconds(1));
    }
}
