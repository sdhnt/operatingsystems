#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void handler(int sig) {
	pid_t pid;
	pid = wait(NULL);
	printf("Child Process %d exited.\n", pid);
}

int main(int argc, char *argv[]) {
	signal(SIGCHLD, handler);

	if (!fork()) {
		printf("Child Process %d\n", getpid());
		exit(0);
	}
	sleep(2);
	printf("Parent Process\n");

	return 0;
} // main
