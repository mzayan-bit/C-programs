#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n ;
    printf("how long is your name? \n");
    scanf("%d",&n);
    char *ptr = (char*)(malloc(n*sizeof(char)));
    printf("enter your name? \n");
    scanf("%s",ptr);
    printf("here is your name %s \n ",ptr);
    free(ptr);
}