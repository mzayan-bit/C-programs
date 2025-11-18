#include <pthread.h>
#include <stdio.h>

typedef struct {
    int id;
    char* text;
} Info;

void* worker(void* arg) {
    Info* data = (Info*)arg;

    printf("Thread %d says: %s\n", data->id, data->text);

    return NULL;
}

int main() {
    pthread_t t[4];
    Info infoArr[4];

    infoArr[0].id = 0; infoArr[0].text = "hello";
    infoArr[1].id = 1; infoArr[1].text = "how";
    infoArr[2].id = 2; infoArr[2].text = "are";
    infoArr[3].id = 3; infoArr[3].text = "you";

    pthread_create(&t[0], NULL, worker, &infoArr[0]);
    pthread_create(&t[1], NULL, worker, &infoArr[1]);
    pthread_create(&t[2], NULL, worker, &infoArr[2]);
    pthread_create(&t[3], NULL, worker, &infoArr[3]);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);

    return 0;
}
