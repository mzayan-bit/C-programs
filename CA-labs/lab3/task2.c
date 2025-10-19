#include<stdio.h>
#include<omp.h>
#include<time.h>

int main()
{
    int A[10],B[10],C[10]; 

    for (int i=0; i<10; i++) {
        A[i] = i ;
        B[i]= i *2 ;
    }

    clock_t begin = clock();

    for (int i=0; i<10; i++) {
        C[i] = A[i] * B[i];
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sequential Time: %f seconds\n", time_spent);
}

