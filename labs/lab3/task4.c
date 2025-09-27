#include<stdio.h>
#include<time.h>
#include<omp.h>

int main()
{
   int sum=0;
   clock_t begin = clock();
   
   for (int i = 1 ; i<1000000;i++)
   {
   	sum = sum + i ;
   }
   clock_t end = clock();
   double time = (double)(end-begin)/CLOCKS_PER_SEC;

   printf("Sequential time of the clock is %f \n",time);
   printf("Final sum of seq is  %d \n",sum );
   
   int sum2 = 0 ;
   clock_t begin2 = clock();
   
   #pragma omp parallel for reduction(+:sum2)
	for (int i=1; i<=1000000; i++) {
		sum2 += i;
	}
	clock_t end2 = clock();

	printf("Sum = %d\n", sum2);
	double time2 = (double)(end2-begin2)/CLOCKS_PER_SEC;
	printf("Parallel  time of the clock is %f \n",time2);
}

