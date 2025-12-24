#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct student{
    int id;
    float marks;
};

void *return_grade(void *p)
{
    struct student *s = (struct student*)p;
    char *grade = (char*)malloc(sizeof(char));

    if(s->marks <= 50)
    {
        *grade = 'F';
    }
    else if(s->marks > 50)
    {
        *grade = 'P';
    }
    return (void*)grade;
}

int main()
{
    struct student s[3];
    pthread_t p[3];
    void *status; 

    for(int i = 0; i < 3; i++)
    {
        printf("Enter ID of student %d: \n", i + 1);
        scanf("%d", &s[i].id);

        printf("Enter marks of student %d: \n", i + 1);
        scanf("%f", &s[i].marks); 

        pthread_create(&p[i], NULL, return_grade, &s[i]);
    }

    for(int i = 0; i < 3; i++)
    {

        pthread_join(p[i], &status);
    
        char *final_grade = (char*)status;
        
        printf("Student ID: %d | Marks: %.2f | Grade: %c\n", s[i].id, s[i].marks, *final_grade);
        free(final_grade);
    }
    return 0;
}