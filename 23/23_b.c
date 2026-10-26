#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
static void h(int s){(void)s;write(1,"ITIMER_VIRTUAL expired\n",23);}
int main(void){signal(SIGVTALRM,h);struct itimerval t={0};t.it_value.tv_sec=10;t.it_value.tv_usec=10;
if(setitimer(ITIMER_VIRTUAL,&t,0)<0){perror("setitimer");return 1;}puts("Busy loop: timer measures user CPU time.");
volatile unsigned long long x=0;for(;;)x++;}
