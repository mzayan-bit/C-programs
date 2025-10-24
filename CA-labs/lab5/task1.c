#include<stdio.h>
#include<omp.h>
int main()
{
	int x = 10;

	#pragma omp parallel private(x)
	{
		x=omp_get_thread_num();
		printf("Thread %d : x = %d \n ",omp_get_thread_num(),x);
	}

	printf("after prallel region : x = %d \n ",x);
	printf("in shared region ");
	#pragma omp parallel shared(x)
	{
			printf("i am thread %d \n ",omp_get_thread_num());
			x+=1;
	}

	printf(" \n total = %d",x);
       //basically private make copy of the variable for each thread and at the end all copies are destroyed and main variable remain unchanged 
       //in shared region race condtion occurs because all threads share the same variable 	
}

