#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main()
{
    int N = 100000;
    int num_threads = 16;
    
    int *arr = (int*)malloc(N * sizeof(int));
    long long *thread_results = (long long*)malloc(num_threads * sizeof(long long));

    for(int i = 0 ; i < N ; i++) {
        arr[i] = i + 1 + 3 * i;
    }
    long long int par_sum = 0;
    double start = omp_get_wtime();

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        long long int partial_sum = 0;

        #pragma omp for
        for(int i = 0 ; i < N ; i++)
        {
            partial_sum += arr[i];
        }

        thread_results[id] = partial_sum;

        #pragma omp barrier

        #pragma omp for ordered
        for(int i = 0; i < num_threads; i++) 
        {
            #pragma omp ordered
            {
                printf("Thread %d finished. Partial Sum: %lld\n", i, thread_results[i]);
                par_sum += thread_results[i]; 
            }
        }
    }
    
    double end = omp_get_wtime();
    printf("\nTotal Parallel Sum: %lld \n", par_sum);
    printf("Time: %f \n", end - start);

    free(arr);
    free(thread_results);
    return 0;
}