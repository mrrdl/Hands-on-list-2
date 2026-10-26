#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
void *work(void *arg){long n=(long)(intptr_t)arg;printf("Thread %ld: pthread_self=%lu\n",n,(unsigned long)pthread_self());return NULL;}
int main(void){pthread_t t[3];for(long i=0;i<3;i++){int e=pthread_create(&t[i],0,work,(void*)(intptr_t)(i+1));if(e){fprintf(stderr,"pthread_create error %d\n",e);return 1;}printf("Created thread %ld: ID=%lu\n",i+1,(unsigned long)t[i]);}for(int i=0;i<3;i++)pthread_join(t[i],0);return 0;}
