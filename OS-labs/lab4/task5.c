#include<stdio.h>
#include<errno.h>

int main(){
    FILE *file = fopen("abc.txt","r");
    if (file==NULL){
        perror("no such file \n ");
        printf("the error number is %d \n",errno);

    }
}