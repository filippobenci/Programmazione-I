#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int val;
  struct elemento* next;
}elem;
typedef elem* elemPtr;

void ordered_insert (elemPtr *lptr, int v);
void insert_list (elemPtr *lptr, int v);
void print_list (elemPtr lptr);

int main ()
{
  int v1, v2;
  elem *list1 = NULL;
  elem *list2 = NULL;
  elem *list3 = NULL;

  while(1)
  {
    scanf("%d", &v1);
    if (v1 < 0) break;
    insert_list(&list1,v1);
  }
  while(1)
  {
    scanf("%d", &v2);
    if (v2 < 0) break;
    insert_list(&list2,v2);
  }

  elemPtr temp1 = list1;
  elemPtr temp2 = list2;

  while(temp1 != NULL)
  {
    while(temp2 != NULL)
    {
      if (temp1->val == temp2->val)
      {
        ordered_insert(&list3,temp1->val);
      }
      temp2 = temp2->next;
    }
    temp1 = temp1->next;
    temp2 = list2;
  }

  print_list(list3);
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

  if((*lptr)->val == v) return;
  ordered_insert(&(*lptr)->next, v);
}

void insert_list (elemPtr *lptr, int v)
{
  elemPtr newPtr;
  newPtr = malloc(sizeof(elem));
  if(newPtr != NULL)
  {
    newPtr->val = v;
    newPtr->next = *lptr;
    *lptr = newPtr;
  }
  else puts ("Memoria esaurita");
}

void print_list (elemPtr lptr)
{
  while(lptr != NULL)
  {
    printf("%d\n", lptr->val);
    lptr = lptr->next;
  }
}
