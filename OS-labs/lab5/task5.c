//Write a C program that reads a file
//  entered by the user and counts the
//  number of lines, words, and characters, 
// displaying the result using both system 
// calls and fprintf. 
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
    char filename[50];
    printf("enter the filename\n");
    scanf("%49s",filename);

    int fd=open(filename,O_RDONLY);
    if(fd==-1){
        perror("error opening file \n");
        return 1;
    }
    int chars=0,words=0,lines=0;
    char buffer[256];
    int bytes;
    int in_word=0;

    while((bytes=read(fd,buffer,sizeof(buffer)))>0)
    {
        for(int i = 0 ;i<bytes;i++)
        {
            char c = buffer[i];
            chars++;
            if(c=='\n')
                lines++;
            if(isspace(c)){ 
                in_word=0;
            }
            else if(!in_word)
            { 
                in_word=1;
                words++;    
            }               
        }
    }   
    close(fd);
    printf("Characters: %d\n", chars);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);

    FILE *fp = fopen(filename,"r");
    if(fp==NULL)
    {
        perror("error opening file \n");
        return 1;
    }
    chars=words=lines=0;
    in_word=0;
    int c;

    while((c=fgetc(fp))!=EOF){
        chars++;
        if(c=='\n')
            lines++;
        if(isspace(c))
            in_word=0;
        else if (!in_word){
            in_word=1;
            words++;
        }
    }
    fclose(fp);
    fprintf(stdout,"using fprintf\n");
    fprintf(stdout,"characters %d\n",chars);
    fprintf(stdout,"words %d\n",words);
    fprintf(stdout,"lines %d\n",lines);
    
}
