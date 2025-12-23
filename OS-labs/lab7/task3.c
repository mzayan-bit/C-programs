#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t pid1,pid2,pid3;
    
    pid1 = fork();

    if(pid1==0)
    {
        printf("child 1  PID : %d \n",getpid());
        exit(0);

    }
    else
    {
        wait(NULL);
        printf("child 1 parent's PID : %d \n",getpid());
        pid2=fork();
        if(pid2==0)
        {
            printf("child 2  PID : %d \n",getpid());
            exit(0);

        }
        else
        {
            wait(NULL);
            printf("child 2 parent's PID : %d \n",getpid());
            pid3=fork();
            if(pid3==0)
            {
                printf("child 3  PID : %d \n",getpid());
                exit(0);

            }
            else{
                wait(NULL);
                printf("child 3 parent's PID : %d \n",getpid());
            }

        }
    }
}