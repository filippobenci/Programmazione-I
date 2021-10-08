#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void f_state1(char c, int* c_state);      // Funzioni che rappresentano gli stati
void f_state2(char c, int* c_state);
void f_state3(char c, int* c_state);


int main ()
{
  char stringa[MAX];    // Dichiaro un array di caratteri di dimensione massima MAX che è uguale a 100
  scanf("%s", stringa);   // Chiedo all'utente di inserire una stringa da tastiera
  int current_state = 0, i = 0;   // Dichiaro una variabile "stato corrente" per poter scorrere tra gli stati e un variabile i che fa da indice per lo scorrimento della stringa
  char current_char;  // Dichiaro una variabile "carattere corrente" per scorrere la stringa carattere per carattere

  void(*automa[3])(char,int*)={f_state1, f_state2, f_state3}; // Dichiaro l'array di puntatori a funzioni

  while(stringa[i] != '\0') // Finche non raggiungo la fine della stringa
  {
    current_char = stringa[i];  // Ogni carattere  della stringa uno alla volta viene salvato nella variabile carattere corrente
    (*automa[current_state])(current_char,&current_state);    // Chiamo l'array di puntatori a funzioni partendo dallo stato corrente che è 0, lo stato corrente fa anche da indice all'array in modo da poter rappresentare la transizione degli stati
    i++;  // Aumento l'indice che serve per lo scorrimento della stringa
  }
  if (current_state == 1)
  {
    printf("Stringa appartenente al linguaggio definito dall'espressione ([a-z] | [0-1])*1\n");       // Se alla fine della stringa lo stato è a 1 significa che la stringa si conclude col numero 1 ed appartiene al linguaggio
    int k = 0;
    int len;
    short flag = 0;
    len = strlen(stringa);                                                  // Per la stampa della sottostringa, trovo la dimensione della stringa di partenza e la scandisco con un altro indice fino ad arrivare alla lunghezza diminuita di 2
    char* stamp = "Sottostringa '011' presente, posizione/i: ";
    while(k < len-2)
    {
      if(stringa[k] == 48 && stringa[k+1] == 49 && stringa[k+2] == 49)        // Se trovo una sequenza di caratteri nella stringa che corrisponde alla sottostringa ricercata allora stampo
      {
        flag = 1;
        printf("%s%5d", stamp, k);
        stamp = "";          // La stampa richiede che vengano rappresentati gli indici di partenza di tutte le sottostringhe presenti nella stringa quindi una volta stampata la parte iniziale di testo, la stringa diventa vuota
      }
      k++;
    }
    if (flag == 1) printf("\n\n");  // Se la sottostringa viene trovata dopo aver stampato gli indici vado a capo e lascio una riga vuota
    if(flag != 1) printf("Nessuna sottostringa '011' presente\n\n");     // Se la stringa non viene aggiornata alla stringa vuota significa che la condizione all'intero del while non si è verificata di conseguenza la sottostringa cercata non è presente
  }
  else
  {
    printf("Stringa NON appartenente al linguaggio definito dall'espressione ([a-z] | [0-1])*1\n\n");
  }
}

void f_state1(char c, int* c_state)   // Funzione dello stato 0
{
  if(c == 48 || (c >= 97 && c <=122))     // Se il carattere della stringa è 0 oppure una lettera minuscola allora lo stato corrente va a 0, in questo caso rimane invariato
    {
      *c_state = 0;
    }
  else if (c == 49)       // Se il carattere della stringa è 1 allora lo stato corrente passa allo stato 1, il suo successivo
  {
    *c_state = 1;
  }
  else      // Se il carattere della stringa non è nessuno dei due precedenti allora lo stato corrente passa allo stato 3, che è lo stato finale, in questo caso significa che la stringa non appartiene al linguaggio
  {
    *c_state = 2;
  }
}

void f_state2(char c, int* c_state)   // Funzione dello stato 1
{
  if (c == 49)                        // Se il carattere della stringa è 1, lo stato corrente passa allo stesso stato perchè siamo già nel caso in cui lo stato è 1
  {
    *c_state = 1;
  }
  else if(c == 48 || (c >= 97 && c <= 122))     // Se il carattere della stringa è 0 o una lettera minuscola lo stato corrente passa allo stato precedente
  {
    *c_state = 0;
  }
  else                                        // Nel caso in cui il carattere della stringa non sia ne una lettera minuscola, ne 0, ne 1 allora significa che non appartiene al linguaggio, di conseguenza si passa allo stato 3, lo stato finale e la stringa non appartiene al linguaggio
  {
    *c_state = 2;
  }
}

void f_state3(char c, int* c_state)     // Funzione dello stato finale
{
  printf("Stringa NON appartenente al linguaggio definito dall'espressione ([a-z] | [0-1])*1\n\n");    // Se lo stato corrente è uguale a 2 allora siamo nello stato finale, ciò significa che durante la lettura della stringa è stato riscontrato un carattere non appartenente al linguaggio, di conseguenza l'intera stringa non appartiene al linguaggio, stampo ed esco dal programma
  exit(EXIT_SUCCESS);
}
