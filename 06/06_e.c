#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
int main(void) {
    const char *path="/tmp/fifo_library";
    unlink(path);
    if (mkfifo(path, 0666) == -1) { perror("mkfifo"); return 1; }
    printf("FIFO created at %s using mkfifo()\n", path);
    return 0;
}
