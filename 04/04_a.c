#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {
    int p[2]; if (pipe(p) == -1) { perror("pipe"); return 1; }
    pid_t a = fork();
    if (a == 0) { close(p[0]); close(1); dup(p[1]); close(p[1]); execlp("ls","ls","-l",(char*)0); perror("execlp ls"); _exit(1); }
    pid_t b = fork();
    if (b == 0) { close(p[1]); close(0); dup(p[0]); close(p[0]); execlp("wc","wc",(char*)0); perror("execlp wc"); _exit(1); }
    close(p[0]); close(p[1]); waitpid(a,NULL,0); waitpid(b,NULL,0); return 0;
}
