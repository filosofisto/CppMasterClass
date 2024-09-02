#include <iostream>

#define _BSB_SOURCE
#include <signal.h>

#include <string.h>

using std::cout, std::endl;

extern const char* const sys_siglist[];

int main()
{
    cout << strsignal(SIGABRT) << '\n';
    cout << strsignal(SIGALRM) << '\n';
    cout << strsignal(SIGBUS) << '\n';
    cout << strsignal(SIGCHLD) << '\n';
    cout << strsignal(SIGCONT) << '\n';
    cout << strsignal(SIGFPE) << '\n';
    cout << strsignal(SIGHUP) << '\n';
    cout << strsignal(SIGINT) << '\n';
    cout << strsignal(SIGKILL) << '\n';
    cout << strsignal(SIGQUIT) << '\n';
    cout << strsignal(SIGTERM) << '\n';
    
    return EXIT_SUCCESS;
}

