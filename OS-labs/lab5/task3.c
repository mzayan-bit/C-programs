#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    char input[20];

    printf("enter 20 characters \n");
    fgets(input,sizeof(input),stdin);

    int count;
    while(input[count]!='\0')
    {
        count++;

    }
    int vowels=0;
    for(int i = 0 ;i<count;i++)
    {
        if(input[i]=='a'|input[i]=='A'|input[i]=='E'
            |input[i]=='e'|input[i]=='i'|input[i]=='I'
            |input[i]=='O'|input[i]=='o'|input[i]=='u'
            |input[i]=='U' )
            vowels++;
    }
    printf("number of vowels are %d \n",vowels);

}