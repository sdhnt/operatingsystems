#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
	pid_t child1, child2,child3, child4;
	int statloc;
  pid_t pid[4];
	/*
	pid_t mainpid = getpid();
  if(getpid()==mainpid)
	{child1=fork();}
	if(getpid()==mainpid)
	{child2 = fork();}
	if(getpid()==mainpid)
	{child3 = fork();}
	if(getpid()==mainpid)
	{child4 = fork();}
  //now we have exactly 4 child processes one one main process
	*/
	for(int i=0;i<4;i++)
	{  if((pid[i]=fork())==0)
		 {break;}//each child does not have any children
	}

		if(pid[1]==0){
		printf("Child Process 1\n"); exit(100);
	  }

	   waitpid(pid[1],&statloc,0);//child process 2 has definitely completed prited


	if(pid[3]==0)
	 {
	 printf("Child Process 2\n"); exit(100);
	 }
	 waitpid(pid[3],&statloc,0);


	 if(pid[0]==0)
 	 { printf("Child Process 3\n"); exit(100);
	  }
		waitpid(pid[0],&statloc,0);


	 if(pid[2]==0)
   	{
   	printf("Child Process 4\n"); exit(100);
   	}
  	waitpid(pid[2],&statloc,0);

	return 0;
} // main
