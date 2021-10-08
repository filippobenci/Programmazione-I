#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int val;
  struct elemento * next;
}elem;
typedef elem* elemPtr;

void insert_head(elemPtr *lptr, int v);
void delete_head(elemPtr *lptr);
void print_list(elemPtr lptr);

int main ()
{
  int valore;
  elem *lista = NULL;
  while(1)
  {
    scanf("%d", &valore);
    if(valore > 0)
    {
      insert_head(&lista,valore);
    }
    else if (valore == 0)
    {
      delete_head(&lista);
    }
    else
    {
      print_list(lista);
      break;
    }
  }
  free(lista);
}

void insert_head(elemPtr* lptr, int v)
{
  elemPtr current = *lptr;
  elemPtr previous = NULL;
  elemPtr newPtr = malloc(sizeof(elem));
  if(newPtr == NULL)
  {
    printf("Memoria esaurita.\n");
    exit(EXIT_FAILURE);
  }
  newPtr->val = v;
  newPtr->next = *lptr;
  *lptr = newPtr;
}

void delete_head(elemPtr* lptr)
{
  if(*lptr == NULL) return;
  else
  {
  elemPtr temp = *lptr;
  *lptr = (*lptr)->next;
  free(temp);
  }
}

void print_list(elemPtr lptr)
{
  elemPtr current;
  current = lptr;
  while(current != NULL)
  {
    printf("%d\n", current->val);
    current = current->next;
  }
}
