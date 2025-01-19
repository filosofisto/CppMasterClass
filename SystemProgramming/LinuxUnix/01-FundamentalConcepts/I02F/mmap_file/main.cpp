#include <iostream>
#include <print>
#include <fcntl.h>      // open
#include <unistd.h>     // close                      
#include <string.h>     // string C functions
#include <sys/mman.h>   // mmap 
                    
const unsigned int MEM_SIZE = 100;

void usage(char** argv)
{
  std::println("Usage:");
  std::println("\t{} <file> <text>", argv[0]);
  std::println("\tWhere <file> - Fileto be mapped");
  std::println("\t      <text> - Text to be synchronized into file (max size: {})", MEM_SIZE);
}

int main(int argc, char** argv)
{
  char *addr;
  int fd;

  if (argc < 2){
    usage(argv);
    return EXIT_FAILURE;
  }

  fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    std::cerr << "Error to open file\n";
    return EXIT_FAILURE;
  }

  addr = static_cast<char*>(mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  if (addr == MAP_FAILED) {
    close(fd);
    std::cerr << "Error to map file\n";
    return EXIT_FAILURE;
  }
  
  if (close(fd) == -1) {
    std::cerr << "Error to close file\n";
    return EXIT_FAILURE;
  }

  std::println("Current content: {}", addr);

  if (argc > 2) {
    if (strlen(argv[2]) >= MEM_SIZE) {
      std::cerr << "Size bigger than max permitted\n";
      return EXIT_FAILURE;
    }

    memset(addr, 0, MEM_SIZE);
    strncpy(addr, argv[2], MEM_SIZE-1);
    if (msync(addr, MEM_SIZE, MS_SYNC) == -1) {
      std::cerr << "Error to sync to file\n";
      return EXIT_FAILURE;
    }

    std::println("Copied {} to shared memory", argv[2]);
  }

  return EXIT_SUCCESS;
}

