#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {
    int p[2]; if (pipe(p) == -1) { perror("pipe"); return 1; }
    pid_t a = fork();
    if (a == 0) {
        close(p[0]); close(STDOUT_FILENO);
        if (fcntl(p[1], F_DUPFD, STDOUT_FILENO) == -1) { perror("fcntl"); _exit(1); }
        close(p[1]); execlp("ls","ls","-l",(char*)0); perror("ls"); _exit(1);
    }
    pid_t b = fork();
    if (b == 0) {
        close(p[1]); close(STDIN_FILENO);
        if (fcntl(p[0], F_DUPFD, STDIN_FILENO) == -1) { perror("fcntl"); _exit(1); }
        close(p[0]); execlp("wc","wc",(char*)0); perror("wc"); _exit(1);
    }
    close(p[0]); close(p[1]); waitpid(a,NULL,0); waitpid(b,NULL,0); return 0;
}
