#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    int sum = 0 ;

    int num1,num2;
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);
    
    sum = num1+num2;
    printf("sum of %d and %d is %d \n " ,num1,num2,sum);
}