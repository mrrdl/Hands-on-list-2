#include <stdio.h>
#include <signal.h>
#include <unistd.h>
static void h(int s,siginfo_t *i,void *c){(void)i;(void)c;const char m[]="SIGINT caught by sigaction\n";write(1,m,sizeof(m)-1);if(s==SIGSEGV||s==SIGFPE)_exit(0);}
int main(void){struct sigaction sa;sa.sa_sigaction=h;sigemptyset(&sa.sa_mask);sa.sa_flags=SA_SIGINFO;
if(sigaction(SIGINT,&sa,0)<0){perror("sigaction");return 1;}
puts("Press Ctrl+C.");for(;;)pause();
return 0;}
