#include <iostream>
#include <signal.h>

const int MAX_TRIES = 3;

static void sigintHandler(int sig)
{
	static int counter = 0;

	if (sig == SIGINT) {
		counter++;

		if (counter == MAX_TRIES) {
			std::cout << "Bye!\n";
			exit(EXIT_SUCCESS);
		}

		std::cout << "\nPress Ctrl+C 3 times to terminate the process\n";
	}
}

int main()
{
	if (signal(SIGINT, sigintHandler) == SIG_ERR) {
		std::cerr << "Error to install SIGINT handler\n";
		return EXIT_FAILURE;
	}

	for(;;) {
		pause();
	}

	return EXIT_SUCCESS;
}
