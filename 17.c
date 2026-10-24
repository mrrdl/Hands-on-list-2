#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
int main(void) {
    key_t key=ftok("/tmp",'S'); if(key==(key_t)-1){perror("ftok");return 1;}
    int id=shmget(key,1024,IPC_CREAT|0666); if(id==-1){perror("shmget");return 1;}
    char *p=(char*)shmat(id,NULL,0); if(p==(void*)-1){perror("shmat");return 1;}
    strcpy(p,"Data stored in shared memory"); printf("Wrote: %s\n",p);
    if(shmdt(p)==-1){perror("shmdt");return 1;} puts("Detached writable mapping.");
    const char *ro=(const char*)shmat(id,NULL,SHM_RDONLY);
    if(ro==(void*)-1){perror("shmat SHM_RDONLY");return 1;}
    printf("Read-only attach sees: %s\n",ro);
    puts("A write through this read-only mapping is not permitted; attempting it would normally cause SIGSEGV.");
    if(shmdt((void*)ro)==-1){perror("shmdt read-only");return 1;}
    if(shmctl(id,IPC_RMID,NULL)==-1){perror("IPC_RMID");return 1;}
    puts("Detached and marked shared memory for removal."); return 0;
}
