#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;
    int num_threads = 8;

    counter = 0;
    #pragma omp parallel num_threads(num_threads)
    {
        counter++;
    }
    printf("Without critical: counter = %d \n",counter);

    counter = 0;
    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp critical
        {
            counter++;
	}
    }
    printf("With critical:    counter = %d \n", counter);

    return 0;
}

