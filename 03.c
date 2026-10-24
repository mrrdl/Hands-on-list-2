#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {
    int p2c[2], c2p[2]; pid_t pid; char buf[128] = {0};
    if (pipe(p2c) || pipe(c2p)) { perror("pipe"); return 1; }
    pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        close(p2c[1]); close(c2p[0]);
        ssize_t n = read(p2c[0], buf, sizeof(buf)-1);
        if (n < 0) { perror("child read"); _exit(1); }
        buf[n] = '\0'; printf("Child got: %s\n", buf);
        const char *reply = "Reply from child";
        write(c2p[1], reply, strlen(reply));
        close(p2c[0]); close(c2p[1]); _exit(0);
    }
    close(p2c[0]); close(c2p[1]);
    const char *msg = "Hello child";
    write(p2c[1], msg, strlen(msg)); close(p2c[1]);
    ssize_t n = read(c2p[0], buf, sizeof(buf)-1);
    if (n < 0) perror("parent read");
    else { buf[n] = '\0'; printf("Parent got: %s\n", buf); }
    close(c2p[0]); waitpid(pid, NULL, 0); return 0;
}
