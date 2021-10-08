#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct candidato{
  char nome[10];
  int voto;
  struct candidato *next;
}cand;

typedef cand* candPtr;

void ordered_insert (candPtr *list, char name[]);
void print_rapp (candPtr list);
//void print_list (candPtr list);
int main ()
{
  FILE *fPtr;
  fPtr = fopen("input.txt", "r");
  if (fPtr == NULL)
  {
    printf("Errore, file non valido.\n");
    exit(EXIT_FAILURE);
  }
  cand *lista = NULL;
  char name1[10];
  char name2[10];

  while(!feof(fPtr))
  {
    fscanf(fPtr, "%[^,],%[^\n]\n",name1,name2);
    ordered_insert(&lista,name1);
    ordered_insert(&lista,name2);
  }
  print_rapp(lista);
  //print_list(lista);
}


void ordered_insert(candPtr *list, char name[])
{
  candPtr temp;
  temp = *list;
  while(temp != NULL)
  {
    if(strcmp(name,temp->nome) == 0)
    {
      temp->voto++;
      return;
    }
    temp = temp->next;
  }

  candPtr new_cand;
  new_cand = malloc(sizeof(cand));
  strcpy(new_cand->nome,name);
  new_cand->voto = 1;

  candPtr previous = NULL;
  candPtr current = *list;

  while(current != NULL && strcmp(name,current->nome)> 0)
  {
    previous = current;
    current = current->next;
  }
  if(previous == NULL)
  {
    new_cand -> next = *list;
    *list = new_cand;
  }
  else
  {
    previous->next = new_cand;
    new_cand->next = current;
  }
}

/*void print_list(candPtr list)
{
  while(list!=NULL)
  {
    printf("%s %d\n", list->nome, list->voto);
    list = list->next;
  }
}*/

void print_rapp(candPtr list)
{
  int max, max2 = 0;
  char name1[10],name2[10];
  max = list->voto;
  candPtr temp;
  temp = list;
  while(temp != NULL)
  {
    if(temp->voto > max)
    {
      max = temp->voto;
      strcpy(name1, temp->nome);
    }
    temp = temp->next;
  }

  temp = list;
  while(temp != NULL)
  {
    if(temp->voto > max2 && temp->voto < max)
    {
      max2 = temp->voto;
      strcpy(name2,temp->nome);
    }
    temp = temp -> next;
  }
  printf("%s con %d voti\n", name1,max);
  printf("%s con %d voti\n", name2,max2);
}
