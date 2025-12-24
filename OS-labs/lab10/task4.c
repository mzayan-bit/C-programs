#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int tickets = 5;
pthread_mutex_t user;
void* ticket(void *p)
{
    int ID=*(int*)p;
    
    pthread_mutex_lock(&user);
    if(tickets>0)
    {tickets--;
        printf("Ticket consumed by %d thread \n",ID);
    }else{
        printf("Ticket sold out for Thread %d\n",ID);
    }
    pthread_mutex_unlock(&user);
    return NULL;
}

int main()
{
    int ids[10];
    pthread_t p[10];
    pthread_mutex_init(&user,NULL);
    
    for(int i=0;i<10;i++)
    {
        ids[i]=i+1;
        pthread_create(&p[i],NULL,&ticket,&ids[i]);
    }
    for(int i=0;i<10;i++)
    {
        pthread_join(p[i],NULL);
    }

    pthread_mutex_destroy(&user);
    return 0;
}