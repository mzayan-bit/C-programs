#include <stdio.h>
#include <omp.h>

#define N 4

int main() {
    int A[N][N] = {
        {1, 2, 3, 4},
        {2, 3, 4, 1},
        {3, 4, 1, 2},
        {4, 1, 2, 3}
    };
    int B[N][N] = {
        {4, 3, 2, 1},
        {1, 2, 3, 4},
        {2, 1, 4, 3},
        {3, 4, 1, 2}
    };
    int C[N][N] = {0};

    double start, end;

    // Without ordered printing
    start = omp_get_wtime();

    #pragma omp parallel for collapse(2) num_threads(4)
    //#pragma omp parallel for private(j, k) shared(A, B, C)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;

            // Print without ordered - may appear out of order
            printf("C[%d][%d] = %d\n", i, j, C[i][j]);
        }
    }

    end = omp_get_wtime();
    printf("Time without ordered: %f seconds\n", end - start);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = 0;

    // With ordered printing
    start = omp_get_wtime();

    #pragma omp parallel for collapse(2) ordered num_threads(4)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;

            #pragma omp ordered
            {
                // Print in proper row-column order
                printf("C[%d][%d] = %d\n", i, j, C[i][j]);
            }
        }
    }

    end = omp_get_wtime();
    printf("Time with ordered: %f seconds\n", end - start);

    return 0;
}

