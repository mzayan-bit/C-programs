#include<stdio.h>
#include<unistd.h>

int main()
{
    char *args[]={"ls","-la",NULL,NULL};
    execvp(args[0],args);
}