#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;
    int i;

    printf("Main Parent [PID: %d] Starting...\n", getpid());

    // Loop 3 times to create 3 Children
    for (i = 1; i <= 3; i++) {
        
        child_pid = fork();

        if (child_pid == 0) {
            printf("  -> Child %d [PID: %d] created.\n", i, getpid());

            // Now, this Child acts as a parent to create a Grandchild
            grandchild_pid = fork();

            if (grandchild_pid == 0) {
                printf("     --> Grandchild of Child %d [PID: %d]\n", i, getpid());
                exit(0); // Grandchild dies
            }
            else {
                wait(NULL); // Child waits for its specific Grandchild
                printf("  -> Child %d is done.\n", i);
                exit(0);    // Child dies
            }
        }
    }

    for (i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Main Parent: All children and grandchildren finished.\n");
    return 0;
}