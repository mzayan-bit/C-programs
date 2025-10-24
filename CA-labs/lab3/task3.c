#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    int A[10], B[10], C[10];
    for (int i = 0; i < 10; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    clock_t begin = clock();
    for (int i = 0; i < 10; i++) {
        C[i] = A[i] * B[i];
    }
    clock_t end = clock();
    double time_sequential = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sequential Time: %f seconds\n\n", time_sequential);

    int thread_counts[] = {0,2, 4}; 
    int num_tests = 3;

    for (int t = 0; t < num_tests; t++) {
        int nthreads = thread_counts[t];
        if (nthreads > 0) {
            omp_set_num_threads(nthreads);
            printf("Running with %d threads:\n", nthreads);
        } else {
            printf("Running with default number of threads:\n");
        }

        double start_time = omp_get_wtime();

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();

            #pragma omp for
            for (int i = 0; i < 10; i++) {
                C[i] = A[i] * B[i];
                printf("Thread %d computes element %d\n", tid, i);
            }
        }

        double end_time = omp_get_wtime();
        printf("Parallel Time: %f seconds\n\n", end_time - start_time);
    }

    return 0;
}

