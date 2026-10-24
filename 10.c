#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <errno.h>
int main(void) {
    struct rlimit lim;
    if(getrlimit(RLIMIT_NOFILE,&lim)==-1)perror("getrlimit");
    else printf("Maximum open file descriptors (soft): %llu, hard: %llu\n",
                (unsigned long long)lim.rlim_cur,(unsigned long long)lim.rlim_max);
    int p[2];
    if(pipe(p)==-1){perror("pipe");return 1;}
#ifdef F_GETPIPE_SZ
    int size=fcntl(p[0],F_GETPIPE_SZ);
    if(size==-1)perror("F_GETPIPE_SZ");
    else printf("Pipe capacity: %d bytes\n",size);
#else
    puts("F_GETPIPE_SZ is unavailable in these headers.");
#endif
    close(p[0]);close(p[1]);return 0;
}
