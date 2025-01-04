#include <iostream>
#include <print>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  using namespace std;
   
  println("[Parent] PID: {}", getpid());

  pid_t cpid = fork();

  if (cpid == -1) {
    cerr << "[Parent] Error to create child\n";
    return EXIT_FAILURE;
  }

  if (cpid == 0) {
    // Child
    cout << "[Child] Created with success\n";
    cout << "[Child] Waiting for kill signal\n";

    pause();
    
    cout << "[Child] The end\n";
    
    _exit(0);
  } else {
    // Parent
    int cstatus;
    waitpid(cpid, &cstatus, 0);

    if (WIFEXITED(cstatus)) {
        cout << "[Parent] Child process terminated normally (exit)\n";
    }
    if (WIFSIGNALED(cstatus)) {
        cout << "[Parent] Child terminated via signal (kill)\n";
        println("[Parent] Signal Value: {}", WTERMSIG(cstatus));
    }
  }

  return EXIT_SUCCESS;
}
