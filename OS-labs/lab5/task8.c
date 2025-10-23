#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char filename[50];
    char content[500];
    int fd;

    printf("Enter filename: ");
    scanf("%49s", filename);
    while (getchar() != '\n'); 

    printf("Enter the content (a paragraph): ");
    fgets(content, sizeof(content), stdin);

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    int length = strlen(content);
    int bytes_written = write(fd, content, length);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    close(fd);
    printf(" Data successfully written to '%s'\n", filename);
    return 0;
}
