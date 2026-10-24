#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(void) {
    key_t key=ftok("/tmp",'Q'); int id=msgget(key,0666);
    if(id==-1){perror("msgget (run 11 first)");return 1;}
    struct msqid_ds ds;
    if(msgctl(id,IPC_STAT,&ds)==-1){perror("IPC_STAT");return 1;}
    printf("Old permissions: %o\n",ds.msg_perm.mode & 0777);
    ds.msg_perm.mode=(ds.msg_perm.mode & ~0777) | 0600;
    if(msgctl(id,IPC_SET,&ds)==-1){perror("IPC_SET (owner/root required)");return 1;}
    puts("Permissions changed to 0600."); return 0;
}
