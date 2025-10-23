#include <stdio.h>

int main() {
    FILE *src = fopen("hello.txt", "r");
    FILE *dest = fopen("output.txt", "w");

    if (!src || !dest) {
        perror("Error opening file");
        return 1;
    }

    int c;
    // while ((c = fgetc(src)) != EOF) {
    //     fprintf(dest, "%c", c);  // write each char to output.txt
    // }
    //     while (fscanf(src, "%99s", word) == 1) {
    //     fprintf(dest, "%s ", word);  // write each word with a space
    // }
    char line[1000];

    while((fgets(line,sizeof(line),src)))
    {
        fprintf(dest,"%s",line);
    }
    fclose(src);
    fclose(dest);

    printf("File copied successfully!\n");
    return 0;
}
