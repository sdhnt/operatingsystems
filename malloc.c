#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int numOfElements = 512;
	char* charArrayPtr[numOfElements];
	int i;

	while (1) {
		for (i = 0; i < numOfElements; i++) {
			charArrayPtr[i] = malloc(numOfElements);
		}

		usleep(50000);

		for (i = 0; i < numOfElements; i++) {
			charArrayPtr[i][0] = 'a';
		}

		usleep(50000);

		for (i = 0; i < numOfElements; i++) {
			free(charArrayPtr[i]);
		}

		usleep(50000);
	}

	return 0;
} // main
