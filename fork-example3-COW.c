#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int counter = 0;

	fork();
	printf("Hello World!The current value of counter: %d\n", counter++);
	fork();
	fork();


	return 0;
} // main
