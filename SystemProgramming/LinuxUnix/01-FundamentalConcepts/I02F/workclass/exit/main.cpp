#include <iostream>
#include <print>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t result = fork();

    if (result == -1) {
        cerr << "Error to create child process\n";
        _exit(EXIT_FAILURE);
    }

    if (result == 0) {
        // Child
        cout << "[Child] Child process create with success\n";
        cout << "[Child] Waiting for term signal (kill)\n";

        pause();

        cout << "Terminating Child\n";
        _exit(EXIT_SUCCESS);
    } else {
        // Parent
        cout << "[Parent] Waiting for Child terminates\n";

        int status;
        waitpid(result, &status, 0);

        if (WIFEXITED(status)) {
            cout << "[Parent] Child terminated normally\n";
        }
        if (WIFSIGNALED(status)) {
            cout << "[Parent] Child terminated via signal " << WTERMSIG(status) << '\n';
        }

        cout << "Terminating Parent\n";
        _exit(EXIT_SUCCESS);

    }

    return EXIT_SUCCESS;
}
