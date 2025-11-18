#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *res(void* arg)
{
    int *result = (int*)malloc(sizeof(int));
    if(result==NULL)
    {
        perror("memory allocation failed");
        return NULL;
    }
    *result = 56;
    return result;
}
int main()
{
    pthread_t p1;
    void *ptr;

    pthread_create(&p1,NULL,res,NULL);
    pthread_join(p1,&ptr);

    printf("Thread returned %d\n",*(int*)ptr);

    free(ptr);
    
}