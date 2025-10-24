#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    int A[10], B[10], C[10];
    for (int i = 0; i < 10; i++) {
        A[i] = i;
        B[i] = i * 2;
        C[i]=i*3;
    }

    clock_t begin = clock();
    int sum=0;
    int product;
    int max=-9999999;
    for (int i = 0; i < 10; i++) {
        sum=sum+A[i];
    }
    for (int i = 0; i < 10; i++) {
        product=product*A[i];
    }
    for (int i = 0; i < 10; i++) {
        if(C[i]>max)
        {
            max=C[i];
        }
    }
    clock_t end = clock();
    double time_sequential = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("sum=%d\n",sum);
    printf("product=%d\n",product);
    printf("max is %d\n",max);
    printf("Sequential Time: %f seconds\n\n", time_sequential);

    double start_time=omp_get_wtime();
    int psum=0;
    int pproduct;
    int pmax=-999999;
    #pragma omp parallel
    {
       #pragma omp sections
       {
            #pragma omp section
            {
                for (int i = 0; i < 10; i++) {
                    psum=psum+A[i];
                }
            }
            #pragma omp section
            {
                    for (int i = 0; i < 10; i++) {
                        pproduct=pproduct*A[i];
                    }
            }
            #pragma omp section
            {
                    for (int i = 0; i < 10; i++) {
                        if(C[i]>pmax)
                        {
                            pmax=C[i];
                        }
                    }
            }
       }
    }

    double end_time = omp_get_wtime();
    printf("parallel sum=%d\n",psum);
    printf("parallel product=%d\n",pproduct);
    printf("parallel  max is %d\n",pmax);
    printf("Parallel Time: %f seconds\n\n", end_time - start_time);
    
    return 0;

}


