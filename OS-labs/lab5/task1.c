#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    char content[100];
    char name[20];
    int fd;
    printf("enter file name please \n");
    scanf("%19s",name);
    printf("enter content please \n");
    scanf("%99s",content);
    
    int lenght = 0 ;
    while(content[lenght]!='\0')
    {
        lenght++;

    }
    fd = open(name,O_WRONLY | O_CREAT | O_TRUNC,0644);
    if(fd==-1){
        perror("error creating file");
        return 1 ;

    }
    int bytes_wr = write(fd,content,lenght);
    if(bytes_wr==-1)
    {
        perror("error wirting to file \n  ");

        close(fd);
        return 1 ;

    }
    close(fd);

    printf("Data successfully written to %s\n", name);
    return 0;
}