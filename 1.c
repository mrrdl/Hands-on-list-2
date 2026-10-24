#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(void) {
    int fd[2]; char buf[128] = {0};
    const char *msg = "Hello through a pipe!";
    if (pipe(fd) == -1) { perror("pipe"); return 1; }
    if (write(fd[1], msg, strlen(msg)) == -1) { perror("write"); return 1; }
    close(fd[1]);
    ssize_t n = read(fd[0], buf, sizeof(buf)-1);
    if (n == -1) { perror("read"); return 1; }
    buf[n] = '\0';
    printf("Read from pipe: %s\n", buf);
    close(fd[0]); return 0;
}
