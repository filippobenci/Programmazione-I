#include <stdio.h>
#include <stdlib.h>

typedef struct numero{
  int n;
  struct numero *next;
}num;
typedef num* numPtr;

void insert_head (numPtr *list, int v);
void insert_one (numPtr *list);
void print_list (numPtr list);

int main ()
{
  int numero;
  num *lista = NULL;
  while(1)
  {
    scanf("%d",&numero);
    if (numero < 0) break;
    insert_head(&lista,numero);
  }
  insert_one(&lista);
  print_list(lista);
}

void insert_head (numPtr *list, int v)
{
  numPtr newNum = malloc(sizeof(num));
  newNum->n = v;
  newNum->next = *list;
  *list = newNum;
}

void insert_one (numPtr *list)
{
  numPtr temp = *list;
  if(temp->n % 2 == 0)
  {
    numPtr newNum = malloc(sizeof(num));
    newNum->n = -1;
    newNum->next = *list;
    *list = newNum;
  }
  if (temp->next == NULL) return;
  insert_one(&(temp->next));
}

void print_list (numPtr list)
{
  while(list != NULL)
  {
    printf("%d -> ",list->n);
    list = list->next;
  }
  printf("NULL\n");
}
