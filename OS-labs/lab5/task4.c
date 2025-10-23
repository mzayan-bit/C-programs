#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char filename[20];
    printf("enter filename:\n");
    scanf("%19s",filename);
    int fd = open(filename,O_RDONLY);
    if(fd==-1){
        perror("error opening file");
        return 1;
    }
    char buffer[100];

    int bytes_r;
    while((bytes_r=read(fd,buffer,sizeof(buffer)))>0){
        write(STDOUT_FILENO,buffer,bytes_r);
    }
    if (bytes_r==-1)
    {
        perror("error reading file ");
        close(fd);
        return 1;
    }
    close(fd);
    

    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
    {
        perror("error opening file \n");
        return 1;
    }
    printf("using fscanf and fprint f \n");
    char word[100];
    while(fscanf(fp,"%99s",word)==1)
    {
        fprintf(stdout,"%s",word);
    }
    fclose(fp);
    //while(fgets(word,sizeof(word),fp)!=NULL)
    //{
    //    fprintf(stdout,"%s",word);
    //}
    //fclose(fp);
    return 0;
}
