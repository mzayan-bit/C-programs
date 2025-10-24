#include<stdio.h>
#include<omp.h>
// The program should print a message from 
//multiple threads, where each thread displays its thread number. 
//b) Compile the program using OpenMP support. 
//c) Run the program with 2 threads, then with 4 threads.
int main(){
    for(int i=2;i<=4;i=i+2)
    {
        omp_set_num_threads(i);
        printf("printing from %d threads \n",i); 
        #pragma omp parallel
        {
            printf("hello , how are you from thread%d \n ",omp_get_thread_num());
        }
    } 
}