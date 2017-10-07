#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int spawn(char* program, char** arg_list) {
	pid_t child_pid;
	/* Duplicate this process. */
	child_pid = fork();
	if (child_pid > 0) {
		wait(NULL);
		/* This is the parent process. */
		return child_pid;
	} else if (child_pid == 0) {
		/* Now execute PROGRAM, searching for it in the path. */
		execvp(program, arg_list);
		/* The execvp function returns only if an error occurs. */
		fprintf(stderr, "an error occurred in execvp\n");
		abort();
	} else {
		printf("A fork error has occurred.\n");
		exit(-1);
	}
}

int main(int argc, char *argv[]) {
	/* The argument list to pass to the ¡§ls¡¨ command. */
	char* arg_list[] = { "ls", /* argv[0], the name of the program. */
	"-l", "/", NULL /* The argument list must end with a NULL. */
	};
	/* Spawn a child process running the ¡§ls¡¨ command. Ignore the
	 returned child process ID. */
	spawn("ls", arg_list);
	printf("\nDone with main program!!!\n");

	return 0;
}
