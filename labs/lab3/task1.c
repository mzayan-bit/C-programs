#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    int thread_counts[] = {2, 4, 8};
    int num_tests = 3;

    for (int i = 0; i < num_tests; i++) {
        int nthreads = thread_counts[i];
        omp_set_num_threads(nthreads);

        clock_t start = clock();

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            int total = omp_get_num_threads();
            printf("Hello from thread %d of %d\n", tid, total);
        }

        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time taken with %d threads: %f seconds\n\n", nthreads, time_taken);
    }

    return 0;
}

