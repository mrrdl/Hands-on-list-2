#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
static void handler(int s){(void)s; const char m[]="SIGALRM via alarm() caught\n";write(1,m,sizeof(m)-1);}
int main(void){if(signal(SIGALRM,handler)==SIG_ERR){perror("signal");return 1;}
alarm(5); puts("Alarm set for 5 seconds."); for(;;) pause();
return 0;}
