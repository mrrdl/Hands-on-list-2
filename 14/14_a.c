#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message { long type; char text[256]; };
int main(void) {
    key_t key=ftok("/tmp",'Q'); int id=msgget(key,IPC_CREAT|0666);
    if(id==-1){perror("msgget");return 1;}
    struct message m;
    puts("Waiting for type 1 message (blocking)...");
    if(msgrcv(id,&m,sizeof(m.text),1,0)==-1){perror("msgrcv");return 1;}
    printf("Received: %s\n",m.text); return 0;
}
