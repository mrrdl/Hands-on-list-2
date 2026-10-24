#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
static void *handle(void *arg) {
    int c=*(int*)arg; free(arg); char b[512]; ssize_t n=read(c,b,sizeof(b)-1);
    if(n>0){b[n]=0;printf("Thread received: %s\n",b);write(c,"Handled by server thread",24);}
    close(c);return NULL;
}
int main(void) {
    int s=socket(AF_INET,SOCK_STREAM,0);if(s<0){perror("socket");return 1;}
    int opt=1;setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_addr.s_addr=INADDR_ANY;a.sin_port=htons(5052);
    if(bind(s,(struct sockaddr*)&a,sizeof(a))<0||listen(s,10)<0){perror("bind/listen");return 1;}
    puts("Pthread server listening on 5052");
    for(;;){int c=accept(s,NULL,NULL);if(c<0){perror("accept");continue;}
        int *arg=malloc(sizeof(int));if(!arg){close(c);continue;}*arg=c;
        pthread_t t;if(pthread_create(&t,NULL,handle,arg)!=0){perror("pthread_create");close(c);free(arg);continue;}
        pthread_detach(t);
    }
}
