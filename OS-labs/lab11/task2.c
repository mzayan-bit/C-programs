#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int fuel = 0; 
pthread_mutex_t fuel_lock;
pthread_cond_t fuel_cond; 

void* car(void* arg) {
    pthread_mutex_lock(&fuel_lock);

    while (fuel < 40) {
        printf("Car: Not enough fuel (%d). Waiting...\n", fuel);
        pthread_cond_wait(&fuel_cond, &fuel_lock);
    }
    printf("Car: Tank full (%d)! Driving away.\n", fuel);
    fuel -= 40;
    
    pthread_mutex_unlock(&fuel_lock);
    return NULL;
}

void* gas_station(void* arg) {
    for (int i=0; i<5; i++) {
        sleep(1);
        pthread_mutex_lock(&fuel_lock);
        
        fuel += 10;
        printf("Station: Added 10 fuel. Total: %d\n", fuel);
        
        pthread_cond_signal(&fuel_cond);
        
        pthread_mutex_unlock(&fuel_lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&fuel_lock, NULL);
    pthread_cond_init(&fuel_cond, NULL); 

    pthread_create(&t1, NULL, car, NULL);
    pthread_create(&t2, NULL, gas_station, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&fuel_lock);
    pthread_cond_destroy(&fuel_cond);
    return 0;
}