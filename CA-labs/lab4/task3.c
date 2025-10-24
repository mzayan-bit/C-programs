
 

#include <stdio.h>
#include <omp.h>

#define SIZE 20

int main() {
    int arr[SIZE] = {23,5,2,73,34,89,2,56, 78, 90, 11, 44, 5,36,100, 29, 31, 7, 66, 50};

    int minVal_reduction = arr[0];
    int maxVal_reduction = arr[0];
    double startA = omp_get_wtime();

    #pragma omp parallel for reduction(min:minVal_reduction) reduction(max:maxVal_reduction)
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] < minVal_reduction)
	{
		minVal_reduction = arr[i];
	}
        if (arr[i] > maxVal_reduction)
	{
	       	maxVal_reduction = arr[i];
	}
    }
    double endA = omp_get_wtime();

    int minVal_critical = arr[0];
    int maxVal_critical = arr[0];
    double startB = omp_get_wtime();

    #pragma omp parallel for shared(minVal_critical,maxVal_critical)
    for (int i = 0; i < SIZE; i++) {
        #pragma omp critical
        {
            if (arr[i] < minVal_critical)
	    {
		    minVal_critical = arr[i];
	    }
            if (arr[i] > maxVal_critical)
	    {
		    maxVal_critical = arr[i];
	    }
        }
    }
    double endB = omp_get_wtime();

    printf("Reduction  Min: %d, Max: %d, Time: %f\n", minVal_reduction, maxVal_reduction, endA - startA);
    printf("Critical  Min: %d, Max: %d, Time: %f\n", minVal_critical, maxVal_critical, endB - startB);

    return 0;
}
	
