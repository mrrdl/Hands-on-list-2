#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
union semun { int val; struct semid_ds *buf; unsigned short *array; };
int main(void) {
    key_t key=ftok("/tmp",'R'); int sem=semget(key,1,IPC_CREAT|0666);
    if(sem<0){perror("semget");return 1;}
    union semun arg; arg.val=2; semctl(sem,0,SETVAL,arg); /* two identical resources */
    struct sembuf acquire={0,-1,0}, release={0,1,0};
    for(int i=0;i<5;i++) if(fork()==0) {
        semop(sem,&acquire,1); printf("PID %ld acquired a resource\n",(long)getpid()); fflush(stdout);
        sleep(2); printf("PID %ld releasing resource\n",(long)getpid()); fflush(stdout);
        semop(sem,&release,1); _exit(0);
    }
    for(int i=0;i<5;i++)wait(NULL);
    semctl(sem,0,IPC_RMID); return 0;
}
