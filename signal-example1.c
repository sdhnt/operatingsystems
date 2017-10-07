#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 5

int main(int argc, char *argv[]) {
	pid_t pid[N];
	int i;
	int child_status;

	for (i = 0; i < N; i++) {
		if ((pid[i] = fork()) == 0) {
			while (1)
				; /* Child: Infinite Loop */
		}
	}
	for (i = 0; i < N; i++) {
		printf("Killing process %d\n", pid[i]);
		kill(pid[i], SIGINT);
	}

	for (i = 0; i < N; i++) {
		pid_t wpid = wait(&child_status);
		if (WIFEXITED(child_status)) {
			printf("Child %d terminated with exit status %d\n", wpid,
					WEXITSTATUS(child_status));
		} else {
			printf("Child %d terminated abnormally\n", wpid);
		}
	}

	return 0;
} // main

