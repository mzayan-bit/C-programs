#include <stdio.h>
#include <unistd.h>

int main() {
    printf("I am the original program. I am about to disappear...\n");
    execlp("grep", "grep", "printf","task3.c", NULL);
    printf("This will only print if there was an error!\n");
    return 0;
}