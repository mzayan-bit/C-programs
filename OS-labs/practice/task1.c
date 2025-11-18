#include<stdio.h>
#include<pthread.h>

void *printA(void *arg)
{
    char* x = (char *)arg;
    for(int i=0;i<5;i++)
    { 
        printf("%s%d\n",x,i);
    }
    return NULL;
}
void *printB(void *arg)
{
    char* x = (char *)arg;
    for(int i=0;i<5;i++)
    { 
        printf("%s%d\n",x,i);
    }
    return NULL;
}

int main()
{
    pthread_t p1,p2;

    pthread_create(&p1,NULL,printA,"A");
    pthread_create(&p2,NULL,printB,"B");

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

}