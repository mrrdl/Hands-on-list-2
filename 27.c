#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
int main(void){long a;
a=sysconf(_SC_ARG_MAX);printf("Maximum exec args/environment bytes: %ld\n",a);
a=sysconf(_SC_CHILD_MAX);printf("Maximum simultaneous processes per user ID: %ld\n",a);
a=sysconf(_SC_CLK_TCK);printf("Clock ticks per second: %ld\n",a);
a=sysconf(_SC_OPEN_MAX);printf("Open file descriptors per process: %ld\n",a);
long page=sysconf(_SC_PAGESIZE);printf("Page size: %ld bytes\n",page);
struct sysinfo s;if(sysinfo(&s)<0){perror("sysinfo");return 1;}
printf("Total physical RAM pages (approx): %llu\n",((unsigned long long)s.totalram*s.mem_unit)/(unsigned long long)page);
printf("Currently free RAM pages (approx): %llu\n",((unsigned long long)s.freeram*s.mem_unit)/(unsigned long long)page);
struct rlimit r;if(getrlimit(RLIMIT_NOFILE,&r)==0)printf("Current open-file soft limit: %llu\n",(unsigned long long)r.rlim_cur);
return 0;}
