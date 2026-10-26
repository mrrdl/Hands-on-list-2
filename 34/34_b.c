#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc,char **argv){if(argc!=2){fprintf(stderr,"Usage: %s PID\n",argv[0]);return 1;}char *e;long p=strtol(argv[1],&e,10);
if(*e||p<=1){fprintf(stderr,"Invalid PID\n");return 1;}if(kill((pid_t)p,SIGSTOP)<0){perror("kill");return 1;}
printf("Sent SIGSTOP to %ld. It cannot be caught. Resume with: kill -CONT %ld\n",p,p);return 0;}
