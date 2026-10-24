#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
union semun { int val; struct semid_ds *buf; unsigned short *array; };
struct sembuf down={0,-1,0}, up={0,1,0};
int main(void) {
    key_t key=ftok("/tmp",'T'); int sem=semget(key,1,IPC_CREAT|0666);
    if(sem==-1){perror("semget");return 1;}
    union semun arg; arg.val=1; if(semctl(sem,0,SETVAL,arg)==-1){perror("SETVAL");return 1;}
    /* The ticket is in shared memory in a full multi-process version. This demo
       protects a shared file counter, so all children see the same value. */
    FILE *f=fopen("/tmp/ticket_counter","a+"); if(!f){perror("fopen");return 1;} fclose(f);
    for(int i=0;i<5;i++) {
        pid_t p=fork();
        if(p==0) {
            if(semop(sem,&down,1)==-1){perror("down");_exit(1);}
            FILE *fp=fopen("/tmp/ticket_counter","r+"); int n=0;
            if(fp){fscanf(fp,"%d",&n); rewind(fp); fprintf(fp,"%d\n",n+1); fflush(fp); fclose(fp);}
            printf("PID %ld got ticket %d\n",(long)getpid(),n+1); fflush(stdout);
            semop(sem,&up,1); _exit(0);
        }
    }
    for(int i=0;i<5;i++) wait(NULL);
    if(semctl(sem,0,IPC_RMID)==-1)perror("IPC_RMID");
    return 0;
}
