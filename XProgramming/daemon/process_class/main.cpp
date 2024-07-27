#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process_stat.h"

int main(int argc, char** argv)
{
fork();
/*
    // 1. fork()
    switch (fork()) {
        case -1: return EXIT_FAILURE;
        case 0:  break;
        default: _exit(EXIT_SUCCESS); 
    }

    // 2. setsid()
*/
	return EXIT_SUCCESS;
}

