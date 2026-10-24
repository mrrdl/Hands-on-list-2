#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(void) {
    const char *path="/tmp/fifo_syscall";
    unlink(path);
    if (mknod(path, S_IFIFO | 0666, 0) == -1) { perror("mknod"); return 1; }
    printf("FIFO created at %s using mknod()\n", path);
    return 0;
}
