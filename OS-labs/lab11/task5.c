#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMTHREADS 10

pthread_mutex_t mtx;
pthread_cond_t cv;
int current_turn = 0;

void *tfunc(void *arg) {
    long rank = (long)arg;

    pthread_mutex_lock(&mtx);
    
    while(current_turn != rank) {
        pthread_cond_wait(&cv, &mtx);
    }

    printf("thread: my turn!, my rank is %ld.\n", rank);
    current_turn++;

    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mtx);

    return NULL;
}

int main() {
    pthread_t tid[NUMTHREADS];
    
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cv, NULL);

    printf("main: creating threads.\n");

    pthread_mutex_lock(&mtx);

    for(long i = 0; i < NUMTHREADS; i++) {
        pthread_create(&tid[i], NULL, tfunc, (void *)i);
    }

    while(current_turn < NUMTHREADS) {
        pthread_cond_wait(&cv, &mtx);
    }
    
    pthread_mutex_unlock(&mtx);

    printf("main: i hope all threads are finished by now!!\n");

    for(int i = 0; i < NUMTHREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);
    return 0;
}