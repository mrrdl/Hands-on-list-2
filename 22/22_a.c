#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
static void reap(int sig){(void)sig; while(waitpid(-1,NULL,WNOHANG)>0){}}
int main(void) {
    signal(SIGCHLD,reap);
    int s=socket(AF_INET,SOCK_STREAM,0);if(s<0){perror("socket");return 1;}
    int opt=1;setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_addr.s_addr=INADDR_ANY;a.sin_port=htons(5051);
    if(bind(s,(struct sockaddr*)&a,sizeof(a))<0||listen(s,10)<0){perror("bind/listen");return 1;}
    puts("Fork server listening on 5051");
    for(;;){int c=accept(s,NULL,NULL);if(c<0){perror("accept");continue;}
        pid_t p=fork();if(p==0){close(s);char b[512];ssize_t n=read(c,b,511);if(n>0){b[n]=0;printf("Child %ld received: %s\n",(long)getpid(),b);write(c,"Handled by child process",25);}close(c);_exit(0);}
        if(p<0)perror("fork");close(c);
    }
}
