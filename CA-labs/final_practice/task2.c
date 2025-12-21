#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main()
{
    int N[10];
    int total_checksum=0;
    
    for(int i =0;i<10;i++)
    {
        N[i]=i+1;
    }

    #pragma omp parallel
    {
       
        #pragma omp master
        {
            printf("Starting Analysis...\n");
        }
        #pragma omp barrier 

        #pragma omp for reduction(+:total_checksum) ordered
        for(int i =0;i<10;i++)
        {
            total_checksum += N[i];

            #pragma omp ordered
            { 
                printf("%d iteration processed by %d thread \n ", i, omp_get_thread_num());
            }
        }

        #pragma omp barrier
        #pragma omp single
        printf("total checksum %d \n",total_checksum);
    }
}