#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char filename[50];
    char buffer[200];
    int fd;
    int bytesRead;
    printf("Enter file name to read: ");
    scanf("%s", filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0';
    printf("\nContent using system call\n%s\n", buffer);
    close(fd);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(fp, 0, SEEK_SET);
    printf("\n Content using fscanf \n");
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);

    fclose(fp);
    return 0;
}
