#include <stdio.h>
#include <omp.h>

int main() {
    int counter_non_atomic = 0;
    int counter_atomic = 0;

    // Set number of threads to 16
    omp_set_num_threads(16);
    #pragma omp parallel shared(counter_non_atomic)
    {
        for (int i = 0; i < 10000; i++) {
            counter_non_atomic++;  // Unsafe increment (race condition)
        }
    }
    #pragma omp parallel shared(counter_atomic)
    {
        for (int i = 0; i < 10000; i++) {
            #pragma omp atomic
            counter_atomic++;  // Safe increment with atomic
        }
    }
    printf("Final counter without atomic: %d\n", counter_non_atomic);
    printf("Final counter with atomic:    %d\n", counter_atomic);

    return 0;
}

