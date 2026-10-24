#include <stdio.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main(void) {
    const char *path="/tmp/lab_select_fifo";
    if(mkfifo(path,0666)==-1 && access(path,F_OK)==-1){perror("mkfifo");return 1;}
    /* O_RDWR keeps a writer endpoint open so read readiness reflects incoming data. */
    int fd=open(path,O_RDWR|O_NONBLOCK); if(fd<0){perror("open");return 1;}
    fd_set set; FD_ZERO(&set); FD_SET(fd,&set);
    struct timeval tv={.tv_sec=10,.tv_usec=0};
    printf("Waiting up to 10 seconds. In another terminal run: echo hello > %s\n",path);
    int rc=select(fd+1,&set,NULL,NULL,&tv);
    if(rc<0){perror("select");close(fd);return 1;}
    if(rc==0) puts("Timeout: no data received within 10 seconds.");
    else { char b[256]; ssize_t n=read(fd,b,sizeof(b)-1); if(n>0){b[n]=0;printf("Received: %s\n",b);} else if(n<0 && errno!=EAGAIN)perror("read"); else puts("FIFO readable, but no data was available."); }
    close(fd); return 0;
}
