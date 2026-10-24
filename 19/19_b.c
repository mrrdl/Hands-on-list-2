#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
union semun { int val; struct semid_ds *buf; unsigned short *array; };
int main(void) {
    key_t sk=ftok("/tmp",'M'), ek=ftok("/tmp",'E');
    int sh=shmget(sk,sizeof(int),IPC_CREAT|0666); if(sh<0){perror("shmget");return 1;}
    int *counter=shmat(sh,NULL,0); if(counter==(void*)-1){perror("shmat");return 1;} *counter=0;
    int sem=semget(ek,1,IPC_CREAT|0666); if(sem<0){perror("semget");return 1;}
    union semun arg; arg.val=1; semctl(sem,0,SETVAL,arg);
    struct sembuf down={0,-1,0},up={0,1,0};
    for(int i=0;i<4;i++) if(fork()==0) {
        for(int j=0;j<10000;j++){semop(sem,&down,1); (*counter)++; semop(sem,&up,1);}
        shmdt(counter); _exit(0);
    }
    for(int i=0;i<4;i++)wait(NULL);
    printf("Expected 40000, actual %d\n",*counter);
    shmdt(counter); shmctl(sh,IPC_RMID,NULL); semctl(sem,0,IPC_RMID); return 0;
}
