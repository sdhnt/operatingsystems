#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t par;
int k=1;
void int_handler(int sig){

}
void tgrandchild()
{
  execl();
}
int main(int argc, char *argv[]) {
    pid_t child;
    int statusreg;
    pid_t grandchild;
    int outpipe[2];
    pipe(outpipe);
    par=getpid();
    child = fork();


    signal(SIGINT, int_handler);




    if (child == 0) {//inside child1
        close(outpipe[0]);
        // child
        child=getpid();

        grandchild = fork();

        if (grandchild > 0) {//inside child2

          tgrandchild();
        }

        else{//grandchild

          pid_t self = getpid();
          execl("/bin/date",*argv, (char *)0);
          exit(0);

        }
        }

    // (grand)parent

    printf("END\n");


    return 0;
}
