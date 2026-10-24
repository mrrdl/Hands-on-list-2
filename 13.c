#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message { long type; char text[256]; };
int main(void) {
    key_t key=ftok("/tmp",'Q'); if(key==(key_t)-1){perror("ftok");return 1;}
    int id=msgget(key,IPC_CREAT|0666); if(id==-1){perror("msgget");return 1;}
    struct message m={.type=1}; strcpy(m.text,"Hello from msgsnd");
    if(msgsnd(id,&m,strlen(m.text)+1,0)==-1){perror("msgsnd");return 1;}
    printf("Sent: %s (queue ID %d). Check with: ipcs -q\n",m.text,id); return 0;
}
