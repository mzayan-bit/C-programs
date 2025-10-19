#include<stdio.h>

int main()
{
    float a , b ;
    printf("please enter any 2 numbers \n");
    scanf("%f,%f",&a,&b);

    printf("sum of  %f and %f is %.2f \n",a,b,a+b);
    printf("difference of  %f and %f is %.2f \n",a,b,a-b);
    printf("product of  %f and %f is %.2f \n",a,b,a*b);
}