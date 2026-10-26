#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main(void){printf("Receiver PID: %ld\n",(long)getpid());struct sigaction sa;sa.sa_handler=SIG_IGN;sigemptyset(&sa.sa_mask);sa.sa_flags=0;
if(sigaction(SIGSTOP,&sa,0)<0)perror("sigaction(SIGSTOP) expected failure");
puts("SIGSTOP cannot be caught, blocked or ignored. Waiting; send SIGSTOP from another terminal.");fflush(stdout);for(;;)pause();}
