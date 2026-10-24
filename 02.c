#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {
    int fd[2]; pid_t pid; char buf[128] = {0};
    if (pipe(fd) == -1) { perror("pipe"); return 1; }
    pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        close(fd[1]);
        ssize_t n = read(fd[0], buf, sizeof(buf)-1);
        if (n < 0) { perror("read"); _exit(1); }
        buf[n] = '\0'; printf("Child received: %s\n", buf);
        close(fd[0]); _exit(0);
    }
    close(fd[0]);
    const char *msg = "Message from parent process";
    if (write(fd[1], msg, strlen(msg)) < 0) perror("write");
    close(fd[1]); waitpid(pid, NULL, 0); return 0;
}
