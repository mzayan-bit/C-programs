#include<stdio.h>
#include<omp.h>
#include<time.h>

int main()
{
   int seq_sum=0;
   clock_t start=clock();
   for(int i =0;i<1000000;i++)
   {
      seq_sum=seq_sum+i;
   }
   clock_t end = clock();
   double time_spent=(double)(end-start)/CLOCKS_PER_SEC;
   printf("Seq sum is %d\n",seq_sum);
   printf("Time for sequential is %f\n",time_spent);

   int par_sum=0;
   double starts=omp_get_wtime();
   #pragma omp parallel for reduction(+:par_sum)
      for(int i =0;i<1000000;i++)
      {
      par_sum=par_sum+i;
      }
   
   double ends=omp_get_wtime();
   printf("parallel sum is %d\n",par_sum);
   printf("parallel time is %f\n",ends-starts);
}