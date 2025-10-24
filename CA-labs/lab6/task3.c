#include <stdio.h>
#include <omp.h>

int main() {
    int n = 20;
    int a[20], c[20];

    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        c[i] = 0;
    }

    double start, end;
    start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * a[i];
        printf("Thread %d computed square of %d = %d\n",
               omp_get_thread_num(), a[i], c[i]);
    }

    end = omp_get_wtime();
    printf("Time without ordered: %f seconds\n\n", end - start);

    start = omp_get_wtime();

    #pragma omp parallel for ordered
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * a[i];
        #pragma omp ordered
        printf("Thread %d computed square of %d = %d\n",
               omp_get_thread_num(), a[i], c[i]);
    }

    end = omp_get_wtime();
    printf("Time with ordered: %f seconds\n", end - start);

    return 0;
}

