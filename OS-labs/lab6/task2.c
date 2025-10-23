#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0){
        perror("fork failed \n");
        return 1;
    }
    if(pid==0){
        int n ;
        printf("enter number of factorial \n");
        scanf("%d",&n);
        if(n<1){
            return n;
        }
        int factorial=1;
        for(int i = 1 ;i<=n;i++)
        {
            factorial=factorial*i;            
        }
        printf("child factorial of %d is %d \n",n,factorial);
    }else{
        wait(NULL);
        printf("Parent: Factorial calculation completed.\n");
    }
    return 0;

}