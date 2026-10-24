#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(void) {
    key_t key=ftok("/tmp",'Q'); int id=msgget(key,0666);
    if(id==-1){perror("msgget");return 1;}
    if(msgctl(id,IPC_RMID,NULL)==-1){perror("IPC_RMID");return 1;}
    printf("Removed message queue ID %d\n",id); return 0;
}
