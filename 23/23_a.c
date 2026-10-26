#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
static void h(int s){(void)s; write(1,"ITIMER_REAL expired\n",20);}
int main(void){signal(SIGALRM,h);struct itimerval t={0};t.it_value.tv_sec=10;t.it_value.tv_usec=10;
if(setitimer(ITIMER_REAL,&t,0)<0){perror("setitimer");return 1;}puts("Waiting for 10 seconds + 10 microseconds wall time...");for(;;)pause();}
