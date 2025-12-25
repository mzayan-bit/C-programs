#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define MAX 5 

int buffer[MAX];
int in=0;
int out=0;
int count=0;

pthread_cond_t not_full;
pthread_cond_t not_empty;
pthread_mutex_t lock;

void *consumer(void *c)
{
    for(int i = 0 ; i < 10 ; i ++)
    {
        sleep(1);
        pthread_mutex_lock(&lock);
        while(count==0)
        {
            pthread_cond_wait(&not_full,&lock);
        }
        int item =buffer[out];
        out =(out+1)%MAX;
        count --;
        printf("consumer took %d count = %d\n",item,count);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
    }
}

void *producer(void *c)
{
    for(int i = 0 ; i < 10 ; i ++)
    {
        sleep(1);
        pthread_mutex_lock(&lock);
        while(count==MAX)
        {
            pthread_cond_wait(&not_empty,&lock);
        }
        buffer[in]=i;
        int item =buffer[in];
        in=(in+1)%MAX;
        count ++;
        printf("producer put %d count = %d\n",item,count);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&not_full,NULL);
    pthread_cond_init(&not_empty,NULL);

    pthread_t p1,p2;
    
    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&p2,NULL,consumer,NULL);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    pthread_mutex_destroy(&lock);
}
