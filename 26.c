#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#if defined(__i386__) || defined(__x86_64__)
static inline uint64_t ticks(void){unsigned int lo,hi;__asm__ volatile("lfence\n\trdtsc":"=a"(lo),"=d"(hi)::"memory");return ((uint64_t)hi<<32)|lo;}
#else
#error "Requires x86/x86-64 TSC."
#endif
int main(void){volatile pid_t p=0;uint64_t a=ticks();for(int i=0;i<100;i++)p=getppid();uint64_t b=ticks();
printf("100 getppid() calls; final PPID=%ld\n",(long)p);printf("TSC ticks elapsed: %llu\n",(unsigned long long)(b-a));puts("TSC ticks are not necessarily nanoseconds.");return 0;}
