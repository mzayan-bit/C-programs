#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n = 500;
    int data[n];

    for (int i = 0; i < n; i++)
        data[i] = (rand() % 991) + 10;

    double start_total = omp_get_wtime();

    int count_div5 = 0;   
    long long sum = 0;    
    int max_val = 0;      
    double start_comp, end_comp;

    // Parallel region with 8 threads
    #pragma omp parallel num_threads(8) shared(data, count_div5) reduction(+:sum) reduction(max:max_val)
    {
        int id = omp_get_thread_num();

        // Master thread logs start
        #pragma omp master
        {
            printf("Computation started with %d threads...\n", omp_get_num_threads());
            start_comp = omp_get_wtime();
        }

        // Compute local sum and max (handled by reduction)
        #pragma omp for
        for (int i = 0; i < n; i++) {
            sum += data[i];
            if (data[i] > max_val)
                max_val = data[i];
        }

        // Synchronize all threads before next phase
        #pragma omp barrier

        // Count how many numbers in this thread’s portion are divisible by 5
        #pragma omp for
        for (int i = 0; i < n; i++) {
            if (data[i] % 5 == 0) {
                #pragma omp atomic
                count_div5++;
            }
        }

        // After all threads finish counting
        #pragma omp barrier

        // Master thread prints final results
        #pragma omp master
        {
            end_comp = omp_get_wtime();
            double avg = (double)sum / n;
            double total_time = omp_get_wtime() - start_total;

            printf("\n===== Parallel Statistics Report =====\n");
            printf("Total elements: %d\n", n);
            printf("Sum of all elements: %lld\n", sum);
            printf("Average value: %.2f\n", avg);
            printf("Maximum value: %d\n", max_val);
            printf("Count of numbers divisible by 5: %d\n", count_div5);
            printf("Computation phase time: %f sec\n", end_comp - start_comp);
            printf("Total program time: %f sec\n", total_time);
            printf("======================================\n");
        }
    }

    return 0;
}
