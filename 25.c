#include <stdio.h>
#include <sys/resource.h>
int main(void){struct rlimit old,n;if(getrlimit(RLIMIT_NOFILE,&old)<0){perror("getrlimit");return 1;}
printf("Before: soft=%llu hard=%llu\n",(unsigned long long)old.rlim_cur,(unsigned long long)old.rlim_max);n=old;
n.rlim_cur=(old.rlim_max==RLIM_INFINITY||old.rlim_max>=64)?64:old.rlim_max;
if(setrlimit(RLIMIT_NOFILE,&n)<0){perror("setrlimit");return 1;}getrlimit(RLIMIT_NOFILE,&n);
printf("After: soft=%llu hard=%llu\n",(unsigned long long)n.rlim_cur,(unsigned long long)n.rlim_max);return 0;}
