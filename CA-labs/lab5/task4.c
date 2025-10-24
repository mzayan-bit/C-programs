#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(8);  // You can set 8 or 16 threads
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Master thread: Starting parallel work\n");
        }
        int tid = omp_get_thread_num();
        printf("Thread %d is working\n", tid);

        // Master thread prints end message once
        #pragma omp master
        {
            printf("Master thread: All work done\n");
        }
    }

    return 0;
}

