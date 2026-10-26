#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int main(void){pid_t p=getpid(),c=fork();if(c<0){perror("fork");return 1;}
if(c==0){printf("Child %ld sends SIGKILL to parent %ld\n",(long)getpid(),(long)p);fflush(stdout);sleep(1);
if(kill(p,SIGKILL)<0){perror("kill");_exit(1);}sleep(1);printf("Child still running; new PPID=%ld\n",(long)getppid());fflush(stdout);_exit(0);}
printf("Parent PID=%ld; child PID=%ld. Parent will be killed.\n",(long)p,(long)c);fflush(stdout);for(;;)pause();}
