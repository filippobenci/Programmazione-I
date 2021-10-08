#include <stdio.h>
#include <stdlib.h>

typedef struct dipendenti{
  int matr;
  char nome[20];
  int mmAssunzione;
  int aaAssunzione;
  int stipendio;
}Dipendente;
typedef Dipendente* dipendentePtr;

void increase_salary(Dipendente a[], int dim, int perc);
void print_out(Dipendente a[],int dim);

int main()
{
  int percentuale,i = 0;
  int N = 4;
  scanf("%d", &percentuale);

  FILE* fPtr;
  fPtr = fopen("input.txt", "r");
  if(fPtr == NULL)
  {
    printf("Errore, file non ben formattato.");
    return 0;
  }

  Dipendente *arr;
  arr = malloc(N*sizeof(Dipendente));

  while(!feof(fPtr))
  {
    fread(&arr[i], sizeof(Dipendente), 1, fPtr);
    i++;
  }
  printf("Matr	Nome	MM	AA	Stipendio\n");
  for (size_t i = 0; i < N ; i++) {
    printf("%d	%s	%d	%d	%d\n",arr[i].matr,arr[i].nome,arr[i].mmAssunzione,arr[i].aaAssunzione,arr[i].stipendio);
  }
  increase_salary(arr,N,percentuale);
  print_out(arr,N);
  free(arr);
}

void increase_salary(Dipendente a[], int dim, int perc)
{
  int temp;
  for (size_t i = 0; i < dim; i++) {
    if(a[i].mmAssunzione < 5 && a[i].aaAssunzione < 2000 || a[i].aaAssunzione < 2000)
    {
      a[i].stipendio = ((a[i].stipendio*perc)/100) + a[i].stipendio;
    }
  }
  return;
}

void print_out(Dipendente a[], int dim)
{
  printf("Matr	Nome	Stipendio\n");
  for (size_t i = 0; i < dim; i++) {
    if(a[i].stipendio > 1200)
    {
      printf("%d	%s	%d\n",a[i].matr,a[i].nome,a[i].stipendio);
    }
  }
  return;
}
