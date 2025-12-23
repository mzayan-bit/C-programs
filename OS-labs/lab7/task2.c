#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("HC: hello from child\n");
        exit(0);
    } 
    else {
        
        printf("HP: hello from parent\n");
        wait(NULL); 
        printf("CT: child has terminated\n");
    }
    
    printf("Bye\n");
    return 0;
}