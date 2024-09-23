#include <iostream>
#include <signal.h>
#include <thread>
#include <chrono>

using std::cout, std::endl, std::cerr;
using std::this_thread::sleep_for, std::chrono::seconds;

size_t count = 0;
const size_t max_sigint = 5;

void handler(int signal)
{
    count++;
    cout << "Ctrl+C pressed!\n"; 
    
    if (count > max_sigint) {
        cout << "Ctrl+C limit achieved! Bye\n";
        _exit(EXIT_SUCCESS);
    }   
}

int main()
{
    if (signal(SIGINT, handler) == SIG_ERR) {
        cerr << "Error to install the signal handler for SIGINT\n";
        abort();
    }

    for (int i{0}; ; ++i) {
        cout << "Waiting " << i << '\n';
        sleep_for(seconds(1));
    }
}
