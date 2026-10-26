#define _GNU_SOURCE
#include <stdio.h>
#include <sys/resource.h>
#define SHOW(n,r) do{struct rlimit x;if(getrlimit(r,&x)==0){printf("%-18s soft=",n);if(x.rlim_cur==RLIM_INFINITY)printf("infinity");else printf("%llu",(unsigned long long)x.rlim_cur);printf(" hard=");if(x.rlim_max==RLIM_INFINITY)puts("infinity");else printf("%llu\n",(unsigned long long)x.rlim_max);}else perror(n);}while(0)
int main(void){
#ifdef RLIMIT_CPU
SHOW("CPU",RLIMIT_CPU);
#endif
#ifdef RLIMIT_FSIZE
SHOW("FILE SIZE",RLIMIT_FSIZE);
#endif
#ifdef RLIMIT_DATA
SHOW("DATA",RLIMIT_DATA);
#endif
#ifdef RLIMIT_STACK
SHOW("STACK",RLIMIT_STACK);
#endif
#ifdef RLIMIT_CORE
SHOW("CORE",RLIMIT_CORE);
#endif
#ifdef RLIMIT_NPROC
SHOW("NPROC",RLIMIT_NPROC);
#endif
#ifdef RLIMIT_NOFILE
SHOW("NOFILE",RLIMIT_NOFILE);
#endif
#ifdef RLIMIT_AS
SHOW("ADDRESS SPACE",RLIMIT_AS);
#endif
#ifdef RLIMIT_MEMLOCK
SHOW("MEMLOCK",RLIMIT_MEMLOCK);
#endif
#ifdef RLIMIT_SIGPENDING
SHOW("SIGPENDING",RLIMIT_SIGPENDING);
#endif
#ifdef RLIMIT_MSGQUEUE
SHOW("MSGQUEUE",RLIMIT_MSGQUEUE);
#endif
return 0;}
