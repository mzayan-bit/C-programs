#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t  pid1,pid2;
    pid1=fork();
    if(pid1<0){
        perror("fork failed\n");
        return 1;
    }
    if (pid1==0){
        printf("child 1 pid = %d parent pid is %d\n",getpid(),getppid());
        return 0;
    }else{
        pid2=fork();
        if(pid2<0){
            perror("fork failed\n");
            return 1;
        }
        if(pid2==0)
        {
            printf("child 2 pid = %d parent pid is %d\n",getpid(),getppid());
            return 0;
        }else{
            wait(NULL);
            wait(NULL);
            printf("parent : all children completed \n");
        }
    }
    
    return 0;
}

