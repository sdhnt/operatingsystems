#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function Declaration
void calculation(int *a, int *b);

int main(int argc, char *argv[]) {
	pid_t pid;
	int a = 8;
	int b = 2;

	pid = fork();
	if (pid < 0) {
		printf("fork() failed!\n");
	} else if (pid == 0) {
		calculation(&a, &b);

	}

	wait(NULL);
	printf("The value of a in parent process: %d\n", a);
	printf("The value of b in parent process: %d\n", b);
	printf("The END of Program!\n");

	return 0;
} // main

void calculation(int *a, int *b) {

		*a = 5;
		*b = 6;


} // calculation
