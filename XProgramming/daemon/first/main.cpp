#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>

int start_as_daemon()
{
  // become background process
  switch (fork()) {
    case -1: return EXIT_FAILURE;
    case 0: break;
    default: _exit(EXIT_SUCCESS);
  }

  // become leader of new session
  if (setsid() == -1) {
    return EXIT_FAILURE;
  }

  // Ensure we are not session leader
  switch (fork()) {
    case -1: return EXIT_FAILURE;
    case 0: break;
    default: _exit(EXIT_SUCCESS)
  }

  // Clear file mode creation mask
  // If daemon create files and directories, they have the required permissions
  umask(0);

  // Change to the root dir
  chdir("/")

  // Close all opened files inherited from its parent
  int maxfd = sysconf(_SC_OPEN_MAX);
  if (maxfd == -1) {
    maxfd = BD_MAX_CLOSE; 
  }

  for (fd = 0; fd < maxfd; fd++) {
    close(fd);
  }

  // Make all 0, 1 and 2 file descriptors refer to /dev/null
  // It ensures that if daemon calls library that perform I/O on these descriptors, those functions won't unexpectedly fail
  // It prevents the possibility that the daemon later opens a file descriptor 1 or 2, which is then written to - and thus corrupted -
  // by a library function that expects to treat these descriptors as standard output and standard error

  close(STDIN_FILENO); // Reopen standard fd's to /dev/null
  fd = open("/dev/null", O_RDWR);

  if (fd != STDIN_FILENO) { // fd should be 0
    return EXIT_FAILURE; 
  }

  if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO) {
    return EXIT_FAILURE;
  }

  if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int main()
{
  std::cout << "----------------------------------------------------\n";
  std::cout << "Daemon Sample";
  std::cout << "----------------------------------------------------\n";
  std::cout << "Monitoring expensive processes...";

  return start_as_daemon();
}
