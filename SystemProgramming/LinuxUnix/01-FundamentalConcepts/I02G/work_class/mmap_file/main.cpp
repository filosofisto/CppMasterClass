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
  if (argc < 2){
    usage(argv);
    return EXIT_FAILURE;
  }

  char* addr;
  int fd;

  // 1. Open file
  fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    std::cerr << "Error do open file\n";
    return EXIT_FAILURE;
  }

  // 2. Memory Mapping I/O
  addr = static_cast<char*>(mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  if (addr == MAP_FAILED) {
    close(fd);
    std::cerr << "Error to create the memory-mapping I/O\n";
    return EXIT_FAILURE;
  }

  // 3. Close file
  if (close(fd) == -1) {
    std::cerr << "Error to close file\n";
    return EXIT_FAILURE;
  }

  // 4. Print current content
  std::println("Current content: {}", addr);

  // 5. Write argv[2] to memory
  if (argc > 2) {
    if (strlen(argv[2]) > MEM_SIZE) {
      std::cerr << "Error on max size\n";
      return EXIT_FAILURE;
    }

    memset(addr, 0, MEM_SIZE);
    strncpy(addr, argv[2], MEM_SIZE-1);

    // 6. Sync memory to file
    if (msync(addr, MEM_SIZE, MS_SYNC) == -1) {
      std::cerr << "Error on sync to file\n";
      return EXIT_FAILURE;
    }

    std::println("Copied {} from memory to file", argv[2]);
  }

  return EXIT_SUCCESS;
}

