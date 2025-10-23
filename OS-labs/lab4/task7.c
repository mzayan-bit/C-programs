#include<stdio.h>

typedef struct{
    int pages;
    int id ;
    float prices ;
    char name[15];

}books;

int main()
{
    int n ;
    
    printf("how many books you want to enter ? \n");
    scanf("%d",&n);
    books book[n];

    for(int i = 0 ; i<n;i++){
        printf("book id %d",i+1);
        printf("enter no.of pages of book \n ");
        scanf("%d",&book[i].pages);
        printf("enter price of book \n ");
        scanf("%f",&book[i].prices);
        printf("enter name of book \n ");
        scanf("%15s",book[i].name);
    }
    printf("Book Records----- \n");
    for(int i = 0 ; i<n;i++)
    {
        printf("Book ID = %d \n pages: %d \n price:%.2f \n name:%s \n \n ",i+1,book[i].pages,book[i].prices,book[i].name);

    }
}
