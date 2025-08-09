#include <iostream>
#include <signal.h>

const int MAX_TIMES = 3;

static void sig_int_handler(int sig)
{
	static int count = 0;

	if (sig == SIGINT) {
		count++;
		
		if (count == MAX_TIMES) {
			std::cout << "Bye!\n";
			exit(EXIT_SUCCESS);
		}

		std::cout << "\nIn case you want to exit, please try Ctrl-C three times\n";
	}
}

int main()
{
	if (signal(SIGINT, sig_int_handler) == SIG_ERR) {
		std::cerr << "Error to install the SIGINT handler\n";
		return EXIT_FAILURE;
	}

	for(;;) {
		pause();
	}

	return EXIT_SUCCESS;
}

