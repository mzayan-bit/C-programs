#include<stdio.h>
#include<omp.h>
#include<time.h>

int main()
{
    int a[10];
    int b[10];
    int c[10];
    for (int i = 0 ; i<10 ; i++)
    {
        a[i]=i;
        b[i]=i*2;
    }
    clock_t start=clock();
    #pragma omp parallel
    {
        for(int i=0;i<10;i++)
        {
            c[i]=a[i]+b[i];
        }
    }
    clock_t end=clock();
    for (int i = 0 ; i<10 ; i++)
    {
        printf("C[%d]=%d\n",i,c[i]);
    }
    double time_spent=(double)(end-start)/CLOCKS_PER_SEC;
    printf("time spent = %f\n",time_spent);

}

