#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <csignal>
#include <chrono>
#include <thread>
#include <random>

void handleSignal( int signal) {
	exit(signal);
}

int randomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

int main() { //kill stuff
	signal(SIGABRT, handleSignal);
	signal(SIGTERM, handleSignal);

	srand(time(NULL));

	struct winsize w; //get term size
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	const int TERM_X = w.ws_col;

	bool running = true;
	int bitStreams[TERM_X];

	printf("\033[121m"); //H4CK3R M0D3

	for (int i = 0; i < TERM_X; i++) {
		bitStreams[i] = randomNumber(-10, 10);
	}

	while (running) {
		for (int i = 0; i < TERM_X; i++) {
			if (bitStreams[i] < 1) {
				printf(" ");
				bitStreams[i] += 1;
				if (bitStreams[i] == 0) {
					bitStreams[i] = randomNumber(-10, 10);
				}
			} else {
				bitStreams[i] -= 1;
				printf("%d", randomNumber(0, 1));
				if (bitStreams[i] == 0) {
					bitStreams[i] = randomNumber(-20, 5);
				}
			}
		}

		printf("\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	printf("\033[0m]"); //Back to normal

	return 0;
}
