#include <iostream>
#include <signal.h>
#include <thread>
#include <chrono>

using std::cout, std::endl, std::cerr;
using std::this_thread::sleep_for, std::chrono::seconds;

static void handler(int signal)
{
    static size_t count{0};

    if (signal == SIGINT) {
        cout << "\nPressed Ctrl+C " << (++count) << '\n';
        return; 
    }

    cout << "Ctrl+\\ (SIGQUIT) pressed! Bye!\n";
    _exit(EXIT_SUCCESS);
}

int main()
{
    if (signal(SIGINT, handler) == SIG_ERR) {
        cerr << "Error to install the signal handler for SIGINT\n";
        abort();
    }
    if (signal(SIGQUIT, handler) == SIG_ERR) {
        cerr << "Error to install the signal handler for SIGQUIT\n";
        abort();
    }

    for (int i{0}; ; ++i) {
        cout << "Waiting " << i << '\n';
        sleep_for(seconds(1));
    }
}
