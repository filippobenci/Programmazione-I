#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    int n;
    struct elemento* next;
}elem;
typedef elem* elemPtr;

void insert_tail(elemPtr *list, int n);
void insert_number(elemPtr *list, int v);
void print_list(elemPtr list);

int main()
{
    int num;
    elem*lista = NULL;
    while(1)
    {
        scanf("%d", &num);
        if(num < 0) break;
        insert_tail(&lista,num);
    }
    int newNum;
    scanf("%d", &newNum);
    insert_number(&lista,newNum);
    print_list(lista);
    free(lista);
}

void insert_tail(elemPtr *list, int n)
{
    if(*list == NULL)
    {
        elemPtr newPtr = malloc(sizeof(elem));
        newPtr->n = n;
        newPtr->next = *list;
        *list = newPtr;
    }
    else
    {
        elemPtr temp = *list;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(elem));
        temp = temp->next;
        temp->n = n;
        temp->next = NULL;
    }
}

void insert_number(elemPtr *list, int v)
{
    int counter = 0;
    elemPtr newPtr = malloc(sizeof(elem));
    newPtr->n = v;
    elemPtr current = *list;
    elemPtr previous = NULL;

    while(current != NULL)
    {
        previous = current;
        current = current->next;
        counter++;
        if(counter == 4)
        {
            previous->next = newPtr;
            newPtr->next = current;
            break;
        }
    }

    if(counter < 4)
    {
        insert_tail(&(*list),v);
    }
}

void print_list(elemPtr list)
{
    while(list!=NULL)
  {
    printf("%d -> ", list->n);
    list = list->next;
  }
  printf("NULL");
  printf("\n");
}
