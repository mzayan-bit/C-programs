#include <stdio.h>
#include <omp.h>
#define ARRAY_SIZE 100

int main() {
    int arr[ARRAY_SIZE];
    int i;

    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i + 1;
    }

    // method A variables
    int sum_atomic = 0;

    // method B variables
    int sum_critical = 0;
    int num_threads;

    // Get number of threads for later use
    #pragma omp parallel
    {
        #pragma omp single
        {
            num_threads = omp_get_num_threads();
        }
    }

    int partial_sums[num_threads];  // For Method B to store partial sums

    // Initialize partial sums to 0
    for (i = 0; i < num_threads; i++) {
        partial_sums[i] = 0;
    }

    // Method A: atomic sum
    #pragma omp parallel for shared(arr, sum_atomic)
    for (i = 0; i < ARRAY_SIZE; i++) {
        #pragma omp atomic
        sum_atomic += arr[i];
    }
    // Method B: private partial sums + atomic update
    #pragma omp parallel shared(arr, partial_sums, sum_critical)
    {
        int tid = omp_get_thread_num();
        int local_sum = 0;

        #pragma omp for
        for (i = 0; i < ARRAY_SIZE; i++) {
            local_sum += arr[i];
        }
        partial_sums[tid] = local_sum;
        #pragma omp atomic
        sum_critical += local_sum;
    }
    printf("Method A (atomic) total sum: %d\n", sum_atomic);

    printf("Method B partial sums per thread:\n");
    for (i = 0; i < num_threads; i++) {
        printf("  Thread %d partial sum: %d\n", i, partial_sums[i]);
    }
    printf("Method B (private sums + atomic) total sum: %d\n", sum_critical);

    return 0;
}

