#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for sleep

#define NUM_THREADS 3

pthread_barrier_t start_gate;

void* runner(void* arg) {
    int id = *(int*)arg;
    
    printf("Runner %d is warming up...\n", id);
    sleep(1); 
    
    printf("Runner %d is ready at the gate!\n", id);

    pthread_barrier_wait(&start_gate);
    
    printf("Runner %d is RUNNING!\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    pthread_barrier_init(&start_gate, NULL, NUM_THREADS);

    for(int i=0; i<NUM_THREADS; i++) {
        ids[i] = i+1;
        pthread_create(&threads[i], NULL, runner, &ids[i]);
    }

    for(int i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&start_gate);
    return 0;
}