/* Utility to print running total of VmPeak and VmSize of a program */
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 204800	// Increase its size for manipulation
char filename[PATH_MAX];

int target_pid;	// The pid of target application
int block_pid; // The pid to be blocked from triggering the change of application

static int usage(char *me) {
	fprintf(stderr, "%s: filename args\n", me);
	fprintf(stderr,
			"Run program, and print VmSize, VmData and VmStk (in KiB) to stdout\n");

	return 0;
}

static int child(int argc, char **argv) {
	char **newargs = malloc(sizeof(char *) * argc);
	int i;

	/* We can't be certain that argv is NULL-terminated, so do that now */
	for (i = 0; i < argc - 1; i++) {
		newargs[i] = argv[i + 1];
	}
	newargs[argc - 1] = NULL;

	/* Launch the child */
	execvp(argv[1], newargs);

	return 0;
}

static void sig_chld(int dummy) {
	int status, child_val;
	int pid;

	(void) dummy;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid < 0) {
		fprintf(stderr, "waitpid failed\n");
		return;
	}

	/*******************************************************************************************/
	// Question 1b
	/* The pid blocked */
	if (pid == block_pid)
		return;

	/* Signal not from children */
	if (pid != target_pid)
	{
		fprintf(stderr, "Recieved SIGCHLD not from Target Application\n");
		fprintf(stderr, "Please input the path to the new target application\n");
		//input stored in a
		char* a="./malloc2";

		kill(target_pid, SIGINT);
		// Write your code here.....
		pid_t child3=fork();
		if(child3==0)
		{
			char* a1[3];
			a1[0]=a;
			a1[1] = " | perl driveGnuplots.pl 4 400 400 400 400 vmsize vmdata vmstk vmrss";
			a1[2]=NULL;
			execvp(a1[0],a1);
		}

    //fork & execvp new process and perl graph it
		return;
	}
	/*******************************************************************************************/

	/* Get child status value */
	if (WIFEXITED(status)) {
		child_val = WEXITSTATUS(status);
		exit(child_val);
	}
}

static int main_loop(char *filename) {
	char *line;
	char *vmsize;
	char *vmdata;
	char *vmstk;
	char *vmrss;

	size_t len;

	FILE *f;

	vmsize = NULL;
	vmdata = NULL;
	vmstk = NULL;
	vmrss = NULL;
	line = malloc(128);
	len = 128;

	f = fopen(filename, "r");
	if (!f)
		return 1;

	/* Read memory size data from /proc/pid/status */
	while (!vmsize || !vmdata || !vmstk || !vmrss) {
		if (getline(&line, &len, f) == -1) {
			/* Some of the information isn't there, die */
			return 1;
		}

		/* Find VmSize */
		if (!strncmp(line, "VmSize:", 7)) {
			vmsize = strdup(&line[7]);
		}

		/* Find VmData */
		else if (!strncmp(line, "VmData:", 7)) {
			vmdata = strdup(&line[7]);
		}
		/* Find VmStk */
		else if (!strncmp(line, "VmStk:", 6)) {
			vmstk = strdup(&line[6]);
		}
		/* Find VmRSS */
		else if (!strncmp(line, "VmRSS:", 6)) {
			vmrss = strdup(&line[6]);
		}
	}
	free(line);

	fclose(f);

	/* Get rid of " kB\n"*/
	len = strlen(vmsize);
	vmsize[len - 4] = 0;
	len = strlen(vmdata);
	vmdata[len - 4] = 0;
	len = strlen(vmstk);
	vmstk[len - 4] = 0;
	len = strlen(vmrss);
	vmrss[len - 4] = 0;

	/* Output results to stdout */
	printf("0:%s\n1:%s\n2:%s\n3:%s\n", vmsize, vmdata, vmstk, vmrss);

	free(vmsize);
	free(vmdata);
	free(vmstk);
	free(vmrss);

	/* Success */
	return 0;
}

int main(int argc, char **argv) {
	struct sigaction act;

	if (argc < 2)
		return usage(argv[0]);

	/*******************************************************************************************/
	// Question 1a
  pid_t child1=fork();

	char *argv1[2];

	if(child1==0)
	{
			//fprintf(stderr, "Child created with pid %d\n",child1);
			argv1[0] = "/usr/bin/xfce4-terminal";
			argv1[1] = NULL;
			execvp(argv1[0],argv1);
			//return child(1, argv1);
	}

	// Write your code here.....
	if(child1!=0){ //if main
	target_pid = fork();
		if (target_pid==0)
		{return child(argc, argv);}
		if(target_pid!=0){ //main function prints
		fprintf(stderr, "New Terminal Spawned. Please send the signal to pid %d\n",getpid());
	}

	}



	/*******************************************************************************************/

	//Set the signal handler function as sig_chld
	act.sa_handler = sig_chld;

	/* We don't want to block any other signals */
	sigemptyset(&act.sa_mask);

	act.sa_flags = SA_NOCLDSTOP;

	if (sigaction(SIGCHLD, &act, NULL) < 0) {
		fprintf(stderr, "sigaction failed\n");
		return 1;
	}

	snprintf(filename, PATH_MAX, "/proc/%d/status", target_pid);

	/* Continual scan of proc */
	while (1) {
		main_loop(filename);
		/* Wait for 0.1 sec */
		usleep(100000);
		snprintf(filename, PATH_MAX, "/proc/%d/status", target_pid);
	}

	return 1;
}
