#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
static void handler(int s){(void)s; const char m[]="SIGFPE caught\n";write(1,m,sizeof(m)-1);}
int main(void){if(signal(SIGFPE,handler)==SIG_ERR){perror("signal");return 1;}
raise(SIGFPE);
return 0;}
