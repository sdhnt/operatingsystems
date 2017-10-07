#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
	pid_t child1, child2;

	if ((child1 = fork()) == 0) {
		if ((child2 = fork()) == 0) {
			printf("Child Process 2\n");
		} else {
			wait(NULL);
			printf("Child Process 1\n");
		}
	} else {
		wait(NULL);
		printf("Parent Process\n");
	}

	return 0;
} // main
