#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
static void handler(int s){(void)s; const char m[]="SIGVTALRM via ITIMER_VIRTUAL caught\n";write(1,m,sizeof(m)-1);}
int main(void){if(signal(SIGVTALRM,handler)==SIG_ERR){perror("signal");return 1;}
struct itimerval t={0}; t.it_value.tv_sec=3; if(setitimer(ITIMER_VIRTUAL,&t,0)<0){perror("setitimer");return 1;} volatile unsigned long long x=0; for(;;)x++;
return 0;}
