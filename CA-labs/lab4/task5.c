#include <stdio.h>
#include <omp.h>
#define N 200

int main() {
    int i, j, k;
    double A[N][N], B[N][N], C[N][N];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 1.0;
            C[i][j] = 0.0;
        }
    double t1 = omp_get_wtime();
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            double s = 0;
            for (k = 0; k < N; k++)
                s += A[i][k] * B[k][j];
            C[i][j] = s;
        }
    double t2 = omp_get_wtime();
    printf("Sequential: %f sec\n", t2 - t1);

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            C[i][j] = 0;

    double t3 = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            double s = 0;
            #pragma omp parallel for reduction(+:s)
            for (k = 0; k < N; k++)
                s += A[i][k] * B[k][j];
            C[i][j] = s;
        }
    double t4 = omp_get_wtime();
    printf("Parallel:   %f sec\n", t4 - t3);

    return 0;
}
