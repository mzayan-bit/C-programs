#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main()
{
    int a[1000] ;
    for(int i=0;i<1000;i++)
    {
        a[i]=rand()%100;
    }
    int sum=0;
    int min=a[0];
    int max=a[0];
    double s1 = omp_get_wtime();
    //--task1
    #pragma omp parallel for reduction(+:sum) reduction(min:min) reduction(max:max)
            for(int i=0;i<1000;i++)
            {
                if(a[i]<min)
                min=a[i];
            }
            for(int i=0;i<1000;i++)
            {
                if(a[i]>max)
                max=a[i];
            }  
            for(int i=0;i<1000;i++)
            {
                sum +=a[i];
            }                      
    double e1 = omp_get_wtime();
    printf("sum is %d \n max is %d \n min is %d\n",sum,max,min);
    printf("time taken for task1 is %f\n",e1-s1);
    //--task2
    int counter =0 ;
    double s2 =omp_get_wtime();
    #pragma omp parallel for shared(counter)
            for(int i = 0 ; i <1000;i++)
            {
                if(a[i]>50)
                {
                    #pragma omp critical
                    counter++;
                }
            }
    double e2 =omp_get_wtime();
    printf("values in array greater then 50 are %d using critical \n",counter);
    printf("time taken for task2 is %f\n",e2-s2);
    //--task3
    int counter2=0;
    double s3 =omp_get_wtime();
    #pragma omp parallel for shared(counter2)
        for(int i = 0 ; i <1000;i++)
        {
            if(a[i]>50)
            {
                #pragma omp atomic
                counter2++;
            }
        }
    double e3 =omp_get_wtime();
    printf("values in array greater then 50 are %d using atmoic \n",counter2);
    printf("time taken for task3 is %f\n",e3-s3);

}