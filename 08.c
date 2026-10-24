#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc,char **argv) {
    const char *in="/tmp/lab_fifo_c2p", *out="/tmp/lab_fifo_p2c";
    if(mkfifo(in,0666)==-1 && access(in,F_OK)==-1){perror("mkfifo");return 1;}
    if(mkfifo(out,0666)==-1 && access(out,F_OK)==-1){perror("mkfifo");return 1;}
    if(argc>1 && strcmp(argv[1],"server")==0) {
        int r=open(in,O_RDONLY); if(r<0){perror("open read");return 1;}
        char b[256]; ssize_t n=read(r,b,255); if(n<0){perror("read");return 1;} b[n]=0; printf("Server received: %s\n",b); close(r);
        int w=open(out,O_WRONLY); if(w<0){perror("open write");return 1;} char *s="Reply from server"; write(w,s,strlen(s)); close(w);
    } else {
        int w=open(in,O_WRONLY); if(w<0){perror("open write");return 1;} char *s="Hello from client"; write(w,s,strlen(s)); close(w);
        int r=open(out,O_RDONLY); if(r<0){perror("open read");return 1;} char b[256]; ssize_t n=read(r,b,255); if(n<0){perror("read");return 1;} b[n]=0; printf("Client received: %s\n",b); close(r);
    } return 0;
}
