#include<stdio.h>
#include<ctype.h>

int main()
{
    char filename[30];
    printf("enter filename \n ");
    scanf("%29s",filename);

    int chars=0,words=0,lines=0;
    int in_word=0;
    char buffer[10000];
    
    FILE *fp =fopen("weather.csv","r");
    if(fp==NULL)
    {
        perror("error opening file \n");
        return 1;
    }
    int c;
    while((c=fgetc(fp))!=EOF){
        chars++;
        if(c=='\n'){ 
            lines++;
        }
        if(isspace(c))
            in_word=0;
        else if(!in_word)
        {
            in_word=1;
            words++;
        }
    }
    fprintf(stdout,"words %d",words);
    fprintf(stdout,"chars %d",chars);
    fprintf(stdout,"lines %d \n",lines);

    FILE *fps  = fopen("weather.csv","r");
    char buffers[10000];
    if(fps==NULL)
    {
        return 1;
    }


    while(fgets(buffers,sizeof(buffers),fps)){
        fprintf(stdout,"%s",buffers);        
    }
    fclose(fps);
}