#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int val;
  struct elemento *next;
}elem;

typedef elem* elemPtr;

void ordered_insert(elemPtr *lptr, int v);
void print_list(elemPtr lptr);

int main()
{
  int valore;
  elem *lista = NULL;
  while(1)
  {
    scanf("%d", &valore);
    if(valore < 0) break;
    ordered_insert(&lista,valore);
  }
  print_list(lista);
  free(lista);
}

void ordered_insert (elemPtr *lptr, int v)
{
  elemPtr newPtr;
  if(*lptr == NULL)
  {
    *lptr = malloc(sizeof(elem));
    (*lptr)->val = v;
    (*lptr)->next = NULL;
    return;
  }

  if((*lptr)->val > v)
  {
    newPtr = malloc(sizeof(elem));
    newPtr->val = v;
    newPtr->next = *lptr;
    *lptr = newPtr;
    return;
  }
  ordered_insert(&(*lptr)->next, v);
}

void print_list (elemPtr lptr)
{
  elemPtr temp = lptr;
  while(temp != NULL)
  {
    printf("%d\n",temp->val);
    temp = temp->next;
  }
}
