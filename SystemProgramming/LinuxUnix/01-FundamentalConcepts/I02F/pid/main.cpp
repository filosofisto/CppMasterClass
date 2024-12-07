#include <iostream>
#include <unistd.h>


int main()
{
  using namespace std;
   
  cout << "PID:  " << getpid() << '\n';
  cout << "PPID: " << getppid() << '\n';

  return EXIT_SUCCESS;
}
