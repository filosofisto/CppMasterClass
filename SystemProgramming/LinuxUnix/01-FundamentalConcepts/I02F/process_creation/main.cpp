#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

void print_process_info(const string& label, pid_t pid, pid_t ppid)
{
    cout << "[" << label << "] " << "My Pid:     " << pid << '\n';
    cout << "[" << label << "] " << "Parent Pid: " << ppid << '\n';
}

int main()
{
    switch (fork()) {
        case 1:
            cout << "Child created with success\n";
            print_process_info("Child", getpid(), getppid());
            cout << "Finalizing child\n";
            exit(0);
        case -1:
            cerr << "Error trying to create a child\n";
            exit(-1);
        default:
            cout << "Parent process after create a child\n";
            print_process_info("Parent", getpid(), getppid());
            cout << "Finalizing parent\n";
            exit(0);
    }

    return EXIT_SUCCESS;
}
