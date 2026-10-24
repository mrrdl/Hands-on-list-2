#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(void) {
    key_t key=ftok("/tmp", 'Q'); if(key==(key_t)-1){perror("ftok");return 1;}
    int id=msgget(key, IPC_CREAT|0666); if(id==-1){perror("msgget");return 1;}
    printf("Key: %ld\nMessage queue ID: %d\n",(long)key,id); return 0;
}
