#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NPRODUCERS 10
#define NCONSUMERS 5
#define BUFFSIZE 10
#define NVALUES 1000

int BUFFER[BUFFSIZE];
int in = 0;             
int out = 0;            
int count = 0;          
int produced_global = 0;
int consumed_global = 0;

pthread_mutex_t mtx;
pthread_cond_t not_full;
pthread_cond_t not_empty;

void *producer(void *arg) {
    while(1) {
        pthread_mutex_lock(&mtx);

        if (produced_global >= NVALUES) {
            pthread_cond_broadcast(&not_full);
            pthread_cond_broadcast(&not_empty);
            pthread_mutex_unlock(&mtx);
            break; 
        }
        while (count == BUFFSIZE && produced_global < NVALUES) {
            pthread_cond_wait(&not_full, &mtx);
        }
        if (produced_global >= NVALUES) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        BUFFER[in] = produced_global; 
        in = (in + 1) % BUFFSIZE;
        count++;
        produced_global++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *consumer(void *arg) {
    while(1) {
        pthread_mutex_lock(&mtx);
        if (consumed_global >= NVALUES) {
            pthread_cond_broadcast(&not_full);
            pthread_cond_broadcast(&not_empty);
            pthread_mutex_unlock(&mtx);
            break;
        }
        while (count == 0 && consumed_global < NVALUES) {
            pthread_cond_wait(&not_empty, &mtx);
        }
        if (consumed_global >= NVALUES && count == 0) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        if (count == 0) {
            pthread_mutex_unlock(&mtx);
            continue;
        }
        out = (out + 1) % BUFFSIZE;
        count--;
        consumed_global++;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main() {
    pthread_t prod[NPRODUCERS];
    pthread_t cons[NCONSUMERS];

    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    for(long i = 0; i < NPRODUCERS; i++)
        pthread_create(&prod[i], NULL, producer, (void*)i);

    for(long i = 0; i < NCONSUMERS; i++)
        pthread_create(&cons[i], NULL, consumer, (void*)i);

    for(int i = 0; i < NPRODUCERS; i++) pthread_join(prod[i], NULL);
    for(int i = 0; i < NCONSUMERS; i++) pthread_join(cons[i], NULL);

    printf("Total Produced: %d\n", produced_global);
    printf("Total Consumed: %d\n", consumed_global);
    
    if(produced_global == NVALUES && consumed_global == NVALUES) {
        printf("SUCCESS: Test Passed. All values handled.\n");
    } else {
        printf("FAILURE: Counts do not match NVALUES.\n");
    }
    
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    
    return 0;
}