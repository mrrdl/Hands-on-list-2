#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {
    int p1[2], p2[2];
    if (pipe(p1) || pipe(p2)) { perror("pipe"); return 1; }
    pid_t a=fork();
    if (a==0) { close(p1[0]); dup2(p1[1],1); close(p1[1]); close(p2[0]); close(p2[1]); execlp("ls","ls","-l",(char*)0); perror("ls"); _exit(1); }
    pid_t b=fork();
    if (b==0) { close(p1[1]); dup2(p1[0],0); close(p1[0]); close(p2[0]); dup2(p2[1],1); close(p2[1]); execlp("grep","grep","^d",(char*)0); perror("grep"); _exit(1); }
    pid_t c=fork();
    if (c==0) { close(p1[0]); close(p1[1]); close(p2[1]); dup2(p2[0],0); close(p2[0]); execlp("wc","wc",(char*)0); perror("wc"); _exit(1); }
    close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
    waitpid(a,NULL,0); waitpid(b,NULL,0); waitpid(c,NULL,0); return 0;
}
