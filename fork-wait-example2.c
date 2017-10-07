#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		printf("Child Process.\n");
		int i = 0;
		for (i = 0; i < 100; i++) {
			if (i % 10 == 0 && i != 0) {
				printf("\n");
			}
			printf("%d\t", i + 1);

		}
		exit(0);
	} else if (pid > 0) {
		printf("\nParent Process.\n");
		int status;
		wait(&status);
		printf("\nChild Reaped.\n");
	} else {
		fprintf(stderr, "fork() Failed");
		exit(-1);
	}
	return 0;
} // main
