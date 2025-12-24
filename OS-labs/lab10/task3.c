#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct BankAccount {
    int balance;
    pthread_mutex_t lock; 
};

void *deposit(void *arg) {
    struct BankAccount *acct = (struct BankAccount*)arg;
    
    for(int i=0; i<100; i++) {
        pthread_mutex_lock(&acct->lock);
        int temp = acct->balance;
        temp = temp + 10;
        acct->balance = temp;
        
        pthread_mutex_unlock(&acct->lock);
    }
    return NULL;
}

int main() {
    struct BankAccount myAccount;
    myAccount.balance = 0;
    
    pthread_mutex_init(&myAccount.lock, NULL);

    pthread_t p[4];

    for(int i=0; i<4; i++) {
        pthread_create(&p[i], NULL, deposit, &myAccount);
    }

    for(int i=0; i<4; i++) {
        pthread_join(p[i], NULL);
    }

    printf("Final Balance: $%d\n", myAccount.balance);

    pthread_mutex_destroy(&myAccount.lock);
    return 0;
}