#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
int main(void) {
    key_t key=ftok("/tmp",'Q'); if(key==(key_t)-1){perror("ftok");return 1;}
    int id=msgget(key,0666); if(id==-1){perror("msgget (run 11 first)");return 1;}
    struct msqid_ds ds; if(msgctl(id,IPC_STAT,&ds)==-1){perror("msgctl");return 1;}
    printf("Queue ID: %d\n",id);
    printf("Mode/permissions: %o\n",ds.msg_perm.mode & 0777);
    printf("UID: %u GID: %u CUID: %u CGID: %u\n",ds.msg_perm.uid,ds.msg_perm.gid,ds.msg_perm.cuid,ds.msg_perm.cgid);
    printf("Last send time: %s",ds.msg_stime ? ctime(&ds.msg_stime) : "never\n");
    printf("Last receive time: %s",ds.msg_rtime ? ctime(&ds.msg_rtime) : "never\n");
    printf("Last change time: %s",ctime(&ds.msg_ctime));
    printf("Bytes currently queued: %lu\n",(unsigned long)ds.__msg_cbytes);
    printf("Messages currently queued: %lu\n",(unsigned long)ds.msg_qnum);
    printf("Maximum bytes allowed: %lu\n",(unsigned long)ds.msg_qbytes);
    printf("PID of last msgsnd: %d\nPID of last msgrcv: %d\n",ds.msg_lspid,ds.msg_lrpid);
    return 0;
}
