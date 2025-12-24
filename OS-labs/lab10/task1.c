#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter = 0; 

void *increment(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        counter = counter + 1; 
        pthread_unlock
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected Counter: 2000000\n");
    printf("Actual Counter:   %lld\n", counter); 

    return 0;
}