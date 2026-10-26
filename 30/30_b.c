#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
static void handler(int s){(void)s; const char m[]="SIGINT caught\n";write(1,m,sizeof(m)-1);}
int main(void){if(signal(SIGINT,handler)==SIG_ERR){perror("signal");return 1;}
puts("Press Ctrl+C."); for(;;) pause();
return 0;}
