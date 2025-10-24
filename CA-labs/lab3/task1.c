#include<stdio.h>
#include<omp.h>


int main()
{
    int thread_c[]={2,4,8};
    int n =3;
    for(int i = 0 ; i < n ;i++)
    {
        int num_of_threads=thread_c[i];
        omp_set_num_threads(num_of_threads);
        double start = omp_get_wtime();
        #pragma omp parallel
        {
            printf("Hello from thread %d of %d threads \n",omp_get_thread_num(),omp_get_num_threads());
        }
        double end=omp_get_wtime();
        printf("Time taken by %d threads is %f\n",num_of_threads,end-start);
    }
}