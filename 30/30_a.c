#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
static void handler(int s){(void)s; const char m[]="SIGSEGV caught\n";write(1,m,sizeof(m)-1);}
int main(void){if(signal(SIGSEGV,handler)==SIG_ERR){perror("signal");return 1;}
raise(SIGSEGV);
return 0;}
