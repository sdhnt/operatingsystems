#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char*argv) {
	pid_t child1, child2, wpid;
	int statusreg;

	printf("START\n" );
	child1 = fork();
	if (child1== 0)
	{
		  child1=getpid();
			child2 = fork();
			if (child2 > 0)//child 1 main
			{
				execl("/bin/ls","ls","-l",(char *)0); kill(getpid(),SIGINT);
			}
			else if(child2==0) {

				child2=getpid();
				waitpid(child1,&statusreg,0);
				execl("/bin/date",argv,(char *)NULL);
				exit(0);
			}
	}
	else {
	
		waitpid(child2,&statusreg,0);
    printf("END\n" );

	return 0;
}
} // main
