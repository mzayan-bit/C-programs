#include <stdio.h>
#include <omp.h>

int main() {
    
    omp_set_num_threads(4);  

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();  // Get thread ID

        // first  Print before barrier
        printf("Thread %d reached before barrier\n", tid);


        #pragma omp barrier

        // Step 3: Print after barrier
        printf("Thread %d passed barrier\n", tid);
    }

    return 0;
}

