#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc,char **argv) {
    const char *ip=argc>1?argv[1]:"127.0.0.1";
    int s=socket(AF_INET,SOCK_STREAM,0);if(s<0){perror("socket");return 1;}
    struct sockaddr_in a={0};a.sin_family=AF_INET;a.sin_port=htons(5050);
    if(inet_pton(AF_INET,ip,&a.sin_addr)!=1){fprintf(stderr,"Invalid IP\n");return 1;}
    if(connect(s,(struct sockaddr*)&a,sizeof(a))<0){perror("connect");return 1;}
    char *msg="Hello from client";write(s,msg,strlen(msg));
    char buf[1024];ssize_t n=read(s,buf,sizeof(buf)-1);if(n>0){buf[n]=0;printf("Server says: %s\n",buf);}
    close(s);return 0;
}
