#include <unistd.h>
int main() {
    char *args[] = {"/bin/ls","-l", NULL};//full path required
    execv("/bin/ls", args);
    return 0;
}

// #include <unistd.h>
// int main() {
//     char *args[] = {"ls", "-l", NULL};  // no full path
//     execvp("ls", args);
//     return 0;
// }

// #include <unistd.h>
// int main() {
//     execl("/bin/ls", "ls", "-l", NULL);
//     return 0;
// }

// #include <unistd.h>
// int main() {
//     execlp("ls", "ls", "-l", NULL);
//     return 0;
// }

