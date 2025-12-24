#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

struct books{
    int id ;
    int pages;
    char author[20];
};

void* book_details(void *p)
{
    struct books *b = (struct books*)p;
    printf("BOOK DETAILS....\n");
    printf("Book ID : %d \n",b->id);
    printf("Book pages : %d \n",b->pages);
    printf("Book Author : %s \n",b->author);
}

int main()
{
    struct books b;
    pthread_t p;

    printf("Enter ID of book \n");
    scanf("%d",&b.id);

    printf("Enter pages of book \n");
    scanf("%d",&b.pages);

    getchar();

    printf("Enter author of book \n");
    fgets(b.author,20,stdin);
    
    pthread_create(&p,NULL,book_details,&b);
    pthread_join(p,NULL);
}
