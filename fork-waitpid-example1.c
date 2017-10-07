#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int status;
	pid_t pid = fork();

	if (pid < 0) {
		// Error Occurred
		fprintf(stderr, "fork() Failed");
		exit(-1);
	} else if (pid == 0) {
		// Child Process
		printf("Child Process.\n");
		exit(128);
	} else {
		// Parent Process
		waitpid(pid, &status, 0);
		printf("Parent Process.\n\n");

		if (WIFEXITED(status)) {
			printf("The child process terminated normally with exit code %d.\n",
					WEXITSTATUS(status));
		}
	}
	return 0;
} // main
