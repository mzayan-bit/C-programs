#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *print(void *p)
{
    printf("hello there from thread %d \n",getpid());
}

int main()
{
    pthread_t p1;
    pthread_create(&p1,NULL,print,NULL);
    pthread_join(p1,NULL);
}