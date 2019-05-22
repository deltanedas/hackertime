#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <csignal>
#include <climits>
#include <cstring>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>

void handleSignal( int signal) {
	printf("\033[0m]"); //Back to normal
	exit(signal);
}

int randomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

int main(int argc, char* argv[]) { //kill stuff
	signal(SIGABRT, handleSignal);
	signal(SIGTERM, handleSignal);

	srand(time(NULL));

	struct winsize w; //get term size
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	const int TERM_X = w.ws_col;

	bool running = true;
	int bitStreams[TERM_X];

	printf("\033[32m"); //H4CK3R M0D3

	int minStart = -10;
	int maxStart = 10;
	int minMod = -20;
	int maxMod = 5;
	int minBlank = -20;
	int maxBlank = 10;

	if (argc > 1) {
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
			printf("Usage: %s minStart maxStart minMod maxMod minBlank maxBlank\n", argv[0]);
			printf("Example: %s -10 20 -10 5 -10 10\n", argv[0]);
			printf("\033[0m"); //Back to normal
			return 0;
		} else {
			minStart = std::atoi(argv[1]);
			if (argc > 2) {
				maxStart = std::clamp(std::atoi(argv[2]), minStart, INT_MAX);
				if (argc > 3) {
					minMod = std::atoi(argv[3]);
					if (argc > 4) {
						maxMod = std::clamp(std::atoi(argv[4]), minMod, INT_MAX);
						if (argc > 5) {
							minBlank = std::atoi(argv[5]);
							if (argc > 6) {
								maxBlank = std::clamp(std::atoi(argv[6]), minBlank, INT_MAX);
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < TERM_X; i++) {
		bitStreams[i] = randomNumber(minStart, maxStart);
	}

	while (running) {
		for (int i = 0; i < TERM_X; i++) {
			if (bitStreams[i] < 1) {
				printf(" ");
				bitStreams[i] += 1;
				if (bitStreams[i] == 0) {
					bitStreams[i] = randomNumber(minBlank, maxBlank);
				}
			} else {
				bitStreams[i] -= 1;
				printf("%d", randomNumber(0, 1));
				if (bitStreams[i] == 0) {
					bitStreams[i] = randomNumber(minMod, maxMod);
				}
			}
		}

		printf("\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	printf("\033[0m"); //Back to normal

	return 0;
}
