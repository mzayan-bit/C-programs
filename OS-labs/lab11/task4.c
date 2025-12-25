#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_cond_t c;
pthread_mutex_t m;
static int result = 0;

void *tfunc(void *arg) {

    // do some work
    pthread_mutex_lock(&m);
    int r = rand()%10;
    sleep(r);
    result = 7;

    printf("thread: produced result.\n");
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&m,NULL);
    pthread_cond_init(&c,NULL);

    printf("main: creating thread.\n");
    pthread_t tid;
    pthread_create(&tid, NULL, tfunc, NULL);
    pthread_mutex_lock(&m);
    while (result == 0) {
        pthread_cond_wait(&c, &m);
    }
    printf("main: result = %d\n", result);
    pthread_mutex_unlock(&m);

    pthread_join(tid, NULL);
    return 0;
}
