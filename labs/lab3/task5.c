#include <stdio.h>
#include <omp.h>
#define N 10000

int main() {
    int A[N], B[N], C[N];
    long long sum = 0, prod = 1, max;
    int i;

    for (i = 0; i < N; i++) {
        A[i] = i + 1;
        B[i] = 2;
        C[i] = N - i;
    }

    // Sequential
    double s = omp_get_wtime();
    sum = 0;
    for (i = 0; i < N; i++) sum += A[i];

    prod = 1;
    for (i = 0; i < N; i++) prod *= B[i];  

    max = C[0];
    for (i = 1; i < N; i++)
        if (C[i] > max) max = C[i];

    double e = omp_get_wtime();
    printf("seq %f\n", e - s);
    printf("sum : %lld product : %lld max : %lld\n", sum, prod, max);

    
    sum = 0; prod = 1; max = C[0];
    double ps = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            long long temp = 0;
            for (i = 0; i < N; i++) temp += A[i];
            sum = temp;
        }
        #pragma omp section
        {
            long long temp = 1;
            for (i = 0; i < N; i++) temp *= B[i]; 
            prod = temp;
        }
        #pragma omp section
        {
            long long temp = C[0];
            for (i = 1; i < N; i++)
                if (C[i] > temp) temp = C[i];
            max = temp;
        }
    }

    double pe = omp_get_wtime();
    printf("par %f\n", pe - ps);
    printf("sum : %lld product : %lld max : %lld\n", sum, prod, max);

    return 0;
}
