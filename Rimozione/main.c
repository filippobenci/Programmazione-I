#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int n;
  struct elemento* next;
}elem;

typedef elem* elemPtr;

void insert_head (elemPtr *list, int v);
void insert_tail (elemPtr *list, int v);
void remove_elem (elemPtr *list, int v);
void print_list (elemPtr list);

int main ()
{
  int val;
  elem *lista = NULL;
  while(1)
  {
    scanf("%d", &val);
    if (val % 2 == 0 && val > 0)
    {
      insert_head(&lista,val);
    }
    if( val % 2 != 0 && val > 0)
    {
      insert_tail(&lista,val);
    }
    if (val < 0)
    {
      remove_elem(&lista,val);
    }
    if (val == 0)
    {
      print_list(lista);
      exit(EXIT_SUCCESS);
    }
  }
}

void insert_head (elemPtr *list, int v)
{
  elemPtr newPtr;
  if(*list == NULL)
  {
    *list = malloc(sizeof(elem));
    (*list)->n = v;
    (*list)->next = NULL;
    return;
  }

  if((*list)->n > v)
  {
    newPtr = malloc(sizeof(elem));
    newPtr->n = v;
    newPtr->next = *list;
    *list = newPtr;
    return;
  }
  insert_head(&(*list)->next, v);
}


void insert_tail (elemPtr *list, int v)
{
  if(*list == NULL)
  {
    elemPtr newPtr = malloc(sizeof(elem));
    newPtr->n = v;
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
    temp->n = v;
    temp->next = NULL;
  }
}

void remove_elem (elemPtr *list, int v)
{
  int x = abs(v);
  if (*list == NULL) return;
  if((*list)->n == x)
  {
    elemPtr temp = *list;
    *list = (*list)->next;
    free(temp);
  }
  else
  {
    elemPtr previous = *list;
    elemPtr current = (*list)->next;
    while(current != NULL && current->n != x)
    {
      previous = current;
      current = current->next;
    }
    if(current != NULL)
    {
      elemPtr temp = current;
      previous->next = current->next;
      free(temp);
    }
  }
}

void print_list (elemPtr list)
{
  while(list != NULL)
  {
    printf("%d\n",list->n);
    list = list->next;
  }
}
