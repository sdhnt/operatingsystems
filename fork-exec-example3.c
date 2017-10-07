#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	pid_t child_pid;
	int status;

	if ((child_pid = fork()) < 0) {
		perror("fork failure");
		exit(1);
	} else if (child_pid == 0) {
		printf("Child Process.\n");
		printf("Child: I will sleep 2 seconds and then execute - date - command \n");

		sleep(2);

		printf("Child: Now, I woke up and am executing date command \n");
		execl("/bin/date", "date", NULL);

		perror("execl() failure!\n");

		printf("This print is after execl() and should not have been executed if execl were successful! \n");
		_exit(1);
	} else {
		printf("Parent Process.\n");
		wait(&status);
		system("ls");
		printf("\n\n");
		printf("Parent: My child is dead. I am going to leave.\n\n");
	}

	return 0;
} // main
