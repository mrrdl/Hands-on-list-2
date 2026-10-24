#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(void) {
    int s=socket(AF_INET,SOCK_STREAM,0); if(s<0){perror("socket");return 1;}
    int opt=1; setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    struct sockaddr_in addr={0}; addr.sin_family=AF_INET; addr.sin_addr.s_addr=INADDR_ANY; addr.sin_port=htons(5050);
    if(bind(s,(struct sockaddr*)&addr,sizeof(addr))<0){perror("bind");return 1;}
    if(listen(s,5)<0){perror("listen");return 1;}
    printf("Server listening on port 5050...\n");
    int c=accept(s,NULL,NULL); if(c<0){perror("accept");return 1;}
    char buf[1024]; ssize_t n=read(c,buf,sizeof(buf)-1);
    if(n>0){buf[n]=0;printf("Client says: %s\n",buf);const char *reply="Hello from server";write(c,reply,strlen(reply));}
    close(c);close(s);return 0;
}
