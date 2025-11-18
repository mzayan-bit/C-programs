#include <pthread.h>
#include <stdio.h>

void* worker(void* arg) {
    char* message = (char*)arg; // cast properly

    printf("%s\n",message); // print message

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_create(&t1,NULL,worker,"Hello");
    pthread_create(&t2,NULL,worker,"From");
    pthread_create(&t3,NULL,worker,"Thread");

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    return 0;
}
