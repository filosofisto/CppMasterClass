#include <iostream>
#include <print>
#include <unistd.h>

using namespace std;

void show_process_info(const string& label) 
{
    println("[{}] PID: {} PPID: {}", label, getpid(), getppid());
}

int main()
{
    pid_t result = fork();

    if (result == -1) {
        cerr << "Error to create child process\n";
        _exit(EXIT_FAILURE);
    }

    if (result == 0) {
        // Child
        show_process_info("Child");
        cout << "Terminating Child\n";
        _exit(EXIT_SUCCESS);
    } else {
        // Parent
        show_process_info("Parent");
        sleep(1);
        cout << "Terminating Parent\n";
        _exit(EXIT_SUCCESS);

    }

    return EXIT_SUCCESS;
}
