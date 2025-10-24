#include<stdio.h>
#include<omp.h>

int main()
{
    #pragma omp parallel
	{
	#pragma omp critical
		printf("hello from %d thread of %d threads \n ",omp_get_thread_num(),omp_get_num_threads());
	
	}

	
	
}
