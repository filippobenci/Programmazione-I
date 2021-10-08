#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Studente {
  char nome[10];
  char cognome[10];
  int voto;
}Stud;

void printIfPassed(Stud* student);

int main ()
{
  FILE *fPtr;
  fPtr = fopen("input.txt", "r");
  if(fPtr == NULL)
  {
    printf("Errore, file non valido.\n");
    return 0;
  }

  Stud *studente;
  studente = (Stud*)malloc(sizeof(Stud));
  int mark;
  char name[10];
  char surname[10];

  while(!feof(fPtr))
  {
    fscanf(fPtr,"%[^;];%[^;];%d\n",name,surname,&mark);
    if(mark > 30 || mark < 1)
    {
      printf("Errore, file non ben formattato.");
      exit(EXIT_FAILURE);
    }
    strcpy(studente->nome,name);
    strcpy(studente->cognome, surname);
    studente->voto = mark;
    printIfPassed(studente);
  }
  fclose(fPtr);
  free(studente);
}

void printIfPassed (Stud*student)
{
  if(student->voto >= 18)
  {
    printf("%10s%10s%4d ESAME SUPERATO\n", student->nome, student->cognome, student->voto);
  }
  else return;

}
