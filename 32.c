#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main(void){struct sigaction sa;sa.sa_handler=SIG_IGN;sigemptyset(&sa.sa_mask);sa.sa_flags=0;
if(sigaction(SIGINT,&sa,0)<0){perror("sigaction");return 1;}puts("Ignoring SIGINT for 5 seconds.");sleep(5);
sa.sa_handler=SIG_DFL;if(sigaction(SIGINT,&sa,0)<0){perror("sigaction");return 1;}puts("SIGINT default restored; press Ctrl+C.");for(;;)pause();}
