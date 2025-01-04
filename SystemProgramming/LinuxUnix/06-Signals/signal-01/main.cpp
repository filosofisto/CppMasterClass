#include <iostream>
#include <signal.h>
#include <string>
#include <print>
#include <string.h> // required by strsignal

using std::cout, std::endl, std::cerr, std::string, std::println;

void show(const string& mnemonic, int signal)
{
    println("{} [{}]: {}", mnemonic, signal, strsignal(signal));
}

int main()
{
    cout << "Signals required by POSIX.1 and ISO/IEC 9945 Standards\n";
    show("SIGABRT", SIGABRT);
    show("SIGALRM", SIGALRM);
    show("SIGFPE", SIGFPE);
    show("SIGHUP", SIGHUP);
    show("SIGILL", SIGILL);
    show("SIGINT", SIGINT);
    show("SIGKILL", SIGKILL);
    show("SIGPIPE", SIGPIPE);
    show("SIGQUIT", SIGQUIT);
    show("SIGSEGV", SIGSEGV);
    show("SIGTERM", SIGTERM);
    show("SIGUSR1", SIGUSR1);
    show("SIGUSR2", SIGUSR2);

    cout << "\nJob Control Signals by POSIX.1 and ISO/IEC 9945 Standards\n";
    show("SIGCHLD", SIGCHLD);
    show("SIGCONT", SIGCONT);
    show("SIGSTOP", SIGSTOP);
    show("SIGTSTP", SIGTSTP);
    show("SIGTTIN", SIGTTIN);
    show("SIGTTOU", SIGTTOU);

    cout << "\nSome optional Signals\n";
    show("SIGBUS", SIGBUS);

#ifndef __APPLE__
    show("SIGPOLL", SIGPOLL);
#endif 

    show("SIGTRAP", SIGTRAP);
    show("SIGSYS", SIGSYS);

    return EXIT_SUCCESS;
}
