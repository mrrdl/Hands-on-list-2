#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(void) {
    char buf[256]; int fd=open("/tmp/lab_fifo",O_RDONLY);
    if(fd<0){perror("open");return 1;}
    ssize_t n=read(fd,buf,sizeof(buf)-1);
    if(n<0){perror("read");close(fd);return 1;}
    buf[n]='\0'; printf("Reader received: %s",buf); close(fd); return 0;
}
