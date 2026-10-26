#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
static void h(int s){(void)s;write(1,"ITIMER_PROF expired\n",20);}
int main(void){signal(SIGPROF,h);struct itimerval t={0};t.it_value.tv_sec=10;t.it_value.tv_usec=10;
if(setitimer(ITIMER_PROF,&t,0)<0){perror("setitimer");return 1;}puts("Busy loop: timer measures user + system CPU time.");
volatile unsigned long long x=0;for(;;)x++;}
