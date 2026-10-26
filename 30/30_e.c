#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
static void handler(int s){(void)s; const char m[]="SIGALRM via ITIMER_REAL caught\n";write(1,m,sizeof(m)-1);}
int main(void){if(signal(SIGALRM,handler)==SIG_ERR){perror("signal");return 1;}
struct itimerval t={0}; t.it_value.tv_sec=5; if(setitimer(ITIMER_REAL,&t,0)<0){perror("setitimer");return 1;} for(;;) pause();
return 0;}
