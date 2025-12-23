//zombie process#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: I am dying now...\n");
        exit(0); 
    } 
    else {
        printf("Parent: I am sleeping. Check 'ps -l' now to see the Zombie!\n");
        sleep(10); 
        printf("Parent: I woke up. Zombie should be gone after I exit.\n");
    }
    return 0;
}