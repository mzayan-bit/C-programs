#include<stdio.h>
#include<omp.h>

#define N 1000
int main()
{
    int a[N];
    int b[N];
    int c[N];

    for(int i = 0 ; i<N;i++)
    {
        a[i]=i+1;
        b[i]=i*2+1;
        c[i]=5*6+i;
    }
    double start1 = omp_get_wtime();
    int sum_seq=0;
    long int prod_seq=1;
    int max_seq=-999999;
    for(int i = 0 ; i<N;i++)
    {
        sum_seq=sum_seq+a[i];
    }
    for(int i = 0 ; i<N;i++)
    {
        prod_seq=prod_seq*b[i];
    }
    for(int i = 0 ; i<N;i++)
    {
        if(max_seq<c[i])
        {
            max_seq=c[i];
        }
    }
    double end1=omp_get_wtime();
    printf("sequential sum is %d \n",sum_seq);
    printf("sequential product is %ld \n",prod_seq);
    printf("sequential max is %d \n",max_seq);
    printf("total sequential time is  %f \n\n",end1-start1);


    double start2 = omp_get_wtime();
    int sum_par=0;
    long int prod_par=1;
    int max_par=-999999;
    omp_set_num_threads(16);
    #pragma omp parallel 
    {
        #pragma omp sections
        {
            #pragma omp section  
            {     
                for(int i = 0 ; i<N;i++)
                {
                    sum_par=sum_par+a[i];
                }
            }
            #pragma omp section 
            {     
                for(int i = 0 ; i<N;i++)
                {
                    prod_par=prod_par*b[i];
                }
            }
            #pragma omp section 
            {     
                for(int i = 0 ; i<N;i++)
                {
                    if(max_par<c[i])
                    {
                        max_par=c[i];
                    }
                }
            }
        }
    }
    double end2=omp_get_wtime();
    printf("parallel sum is %d \n",sum_par);
    printf("parallel product is %ld \n",prod_par);
    printf("parallel max is %d \n",max_par);
    printf("total parallel time is  %f \n",end2-start2);
}