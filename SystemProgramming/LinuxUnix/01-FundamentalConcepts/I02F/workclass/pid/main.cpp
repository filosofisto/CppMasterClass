#include <iostream>
#include <print>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t pid  = getpid();
    pid_t ppid = getppid();

    println("My PID:     {}", pid);
    println("Parent PID: {}", ppid);

    return EXIT_SUCCESS;
}
