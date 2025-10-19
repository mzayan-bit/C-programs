#include<stdio.h>

int main()
{
    int age ;
    char name[26];
    float gpa ;

    
    printf("enter your name \n");
    scanf("%25s",name);
    printf("enter your age \n");
    scanf("%d",&age);
    printf("enter your gpa \n");
    scanf("%f",&gpa);

    printf(" your name %s, age %d  and gpa %f  \n ",name,age,gpa);

}