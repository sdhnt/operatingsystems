#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
	pid_t child1, child2,child3, child4;
	int statloc, statloc2, statloc3, statloc4;
	pid_t mainpid=getpid();
  pid_t pid[4];
   printf("The START of the Program!\n");
	for(int i=0;i<4;i++)
	{  if((pid[i]=fork())==0)
		 {break;}//each child does not have any children
	}
if(getpid()==mainpid)
{


				pid_t wpi2=waitpid(pid[1],&statloc,0);//child process 2 has definitely completed prited
	 			pid_t wpi4=waitpid(pid[3],&statloc2,0);
				pid_t wpi1=waitpid(pid[0],&statloc3,0);
  			pid_t wpi3=waitpid(pid[2],&statloc4,0);

				printf("Child Process %d...\n", WEXITSTATUS(statloc) );//printed becuase of process 2
				printf("Child Process %d...\n",  WEXITSTATUS(statloc2) );//printed becuase of process 4
				printf("Child Process %d...\n", WEXITSTATUS(statloc3)  );//printed becuase of process 1
				printf("Child Process %d...\n", WEXITSTATUS(statloc4) );//printed becuase of process 3
				printf("The END of the Program!\n");
}

	 else
	 {

		 if(pid[0]==0)
	   {  exit(3);//exits returning the child number to be printed
	    }

		 if(pid[1]==0){
		 exit(1);
	  }
		if(pid[2]==0)
		{
		 exit(4);
		 }
		 if(pid[3]==0)
		 {
			 exit(2);
		 }


     }




	return 0;
} // main
