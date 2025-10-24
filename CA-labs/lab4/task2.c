#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main()
{
	int n = 10000000;
	int *arr = (int*)malloc(n*sizeof(int));

	for(int i = 0 ; i <n;i++)
	{
		arr[i]=1;
	}
	double start_seq = omp_get_wtime();
	long long  seq_sum = 0;

	for(int i = 0 ; i <= n ;i ++)
	{
		seq_sum=seq_sum+arr[i];
	}
	double end_seq = omp_get_wtime();
	double start_par=omp_get_wtime();
    long long par_sum = 0 ;
	#pragma omp parallel for reduction(+:par_sum)
	for(int i = 0 ; i <= n ;i ++)
	{
		par_sum=par_sum+arr[i];
	}
	double end_par=omp_get_wtime();

	printf("seq sum : %lld \n ",seq_sum);
	printf("par sum : %lld \n ",par_sum);

	printf("seq time : %f \n ",end_seq-start_seq);
	printf("par time : %f \n ",end_par-start_par);

	free(arr);
	return 0 ; 

}

