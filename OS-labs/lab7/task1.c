#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   pid_t pid, mypid, myppid;
   
   pid = getpid();
   printf("Before fork: Process id is %d\n", pid); 

   pid = fork(); 

   if (pid < 0) {
      perror("fork() failure\n");
      return 1;
   }

   if (pid == 0) { 
      printf("This is child process\n");
      mypid = getpid();
      myppid = getppid();
      printf("Child: My PID is %d, Parent PID is %d\n", mypid, myppid);
   } 
   else { 
      sleep(2); 
      printf("This is parent process\n");
      mypid = getpid();
      myppid = getppid(); 
      printf("Parent: My PID is %d, Parent PID is %d\n", mypid, myppid);
      printf("Parent: I created a child with PID %d\n", pid);
   }
   return 0;
}