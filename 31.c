#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main(void){if(signal(SIGINT,SIG_IGN)==SIG_ERR){perror("signal");return 1;}puts("SIGINT ignored for 5 seconds; try Ctrl+C.");sleep(5);
if(signal(SIGINT,SIG_DFL)==SIG_ERR){perror("signal");return 1;}puts("SIGINT reset to default; Ctrl+C now terminates.");for(;;)pause();}
