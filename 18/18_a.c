#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun { int val; struct semid_ds *buf; unsigned short *array; };
int main(void) {
    key_t key=ftok("/tmp",'B'); int id=semget(key,1,IPC_CREAT|0666);
    if(id==-1){perror("semget");return 1;}
    union semun arg; arg.val=1;
    if(semctl(id,0,SETVAL,arg)==-1){perror("SETVAL");return 1;}
    printf("Binary semaphore ID=%d, initialized to 1\n",id); return 0;
}
