#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
union semun { int val; struct semid_ds *buf; unsigned short *array; };
int main(void) {
    int a=semget(IPC_PRIVATE,1,0600|IPC_CREAT), b=semget(IPC_PRIVATE,1,0600|IPC_CREAT);
    if(a<0||b<0){perror("semget");return 1;}
    union semun arg; arg.val=1; semctl(a,0,SETVAL,arg); semctl(b,0,SETVAL,arg);
    pid_t p=fork();
    if(p==0) {
        struct sembuf takeA={0,-1,0},takeB={0,-1,0};
        semop(a,&takeA,1); puts("Child locked A; waiting for B"); fflush(stdout); sleep(1);
        semop(b,&takeB,1); puts("Child acquired B"); _exit(0);
    } else {
        struct sembuf takeB={0,-1,0},takeA={0,-1,0};
        semop(b,&takeB,1); puts("Parent locked B; waiting for A"); fflush(stdout); sleep(1);
        semop(a,&takeA,1); puts("Parent acquired A"); wait(NULL);
    }
    /* This point is unreachable during the intended deadlock. Remove with ipcrm
       after stopping the program; IPC_PRIVATE IDs are printed by ipcs -s. */
    return 0;
}
