#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(void) {
    char c; printf("Remove semaphore with key from /tmp and project tag? Enter B, C, T, M, E, or R: ");
    if(scanf(" %c",&c)!=1)return 1;
    int tag=(c=='B'?'B':c=='C'?'C':c=='T'?'T':c=='M'?'M':c=='E'?'E':c=='R'?'R':0);
    if(!tag){puts("Unknown tag");return 1;}
    key_t key=ftok("/tmp",tag); int id=semget(key,1,0666);
    if(id==-1){perror("semget");return 1;}
    if(semctl(id,0,IPC_RMID)==-1){perror("IPC_RMID");return 1;}
    printf("Removed semaphore ID %d\n",id); return 0;
}
