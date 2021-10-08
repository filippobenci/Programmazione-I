#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M 100       // Definisco una macro M che rappresenta il numero massimo che può essere scelto come numero segreto
#define DIM 3       // Definisco una macro DIM che rappresenta la dimensione dell'array di puntatori a funzione

void due_giocatori ();      // Dichiarazione del prototipo di funzione per il gioco a due giocatori
void tre_giocatori();       // Dichiarazione del protitipo di funzione per il gioco a tre giocatori
void esci();                // Dichiarazione del prototipo di funzione per l'uscita dal gioco


int main()
{
  int scelta;

  void (*f[DIM])() = {due_giocatori,tre_giocatori,esci};      // Dichiaro un array di puntatori a funzioni alle quali non vengono passati argomenti

  printf("1 - gioco con due giocatori\n2 - gioco con tre giocatori\n3 - esci\nScelta: ");     // Stampo il menu testuale

  while(scanf("%d", &scelta) != 1 || scelta > 3 || scelta <= 0)     // Chiedo all'utente di scegliere una delle funzioni presenti nel menu
  {
    printf("Errore. Opzione non consentita. ");                     // In caso di errore dell'input da tastiera, all'utente viene chiesto di inserire un numero valido
    printf("Scelta: ");
      scanf("%*[^\n]%*c");
  }

  if(scelta < 3 && scelta > 0)                                      // Se la scelta è tra 0 e 3 chiamo la funzione che si trova nella posizione "scelta - 1" dell'array
    {
      (*f[scelta-1])();
    }
  if (scelta == 3)                                                  // Se la scelta è 3 chiamo la funzione di uscita ed esco dal programma
    {
      esci();
      return EXIT_SUCCESS;
    }
  main();                                                           // Passo ricorsivo che richiama la funzione main in modo da poter continuare a giocare finchè non viene scelta la funzione di uscita
}

void due_giocatori()
{
  int a;
  int max = round(log2(M));                                 // Dichiaro una variabile max che rappresenta il numero massimo di tentativi che ha il giocatore per indovinare il numero, il numero massimo è logaritmo in base due di M
  printf("Numero segreto:");
  while(scanf("%d", &a) != 1 || a > M || a < 0)             // Chiedo all'utente di inserire un numero segreto compreso tra 0 e M
  {
    scanf("%*[^\n]%*c");
  }

  printf(" Indovina il numero!\n");

  int numero;

  for (int i = 0; i <  max; i++) {                        // Eseguo un ciclo che va da 0 a max-1 che serve per effettuare i max tentativi
    printf("Tentativo numero %d:", i+1);
    while(scanf("%d", &numero) != 1 || numero > M)
    {
      scanf("%*[^\n]%*c");
    }
    if(numero < a)                                        // Se il numero inserito dal giocatore risulta minore del numero segreto allora suggerisco al giocatore che il suo numero è piu basso
    {
      printf(" Troppo basso\n");
    }
    else if (numero > a)
    {
      printf(" Troppo alto\n");                           // Se il numero inserito dal giocatore risulta maggiore del numero segreto allora suggerisco al giocatore che il suo numero è piu alto
    }
    else if (numero == a)                                 // Se il numero inserito dal giocatore è uguale al numero segreto il giocatore ha vinto
    {
    printf(" Hai vinto!\n");
    return;
    }
  }
  printf("Ha vinto il banco!\n");                         // Se si raggiunge il numero massimo di tentativi senza aver indovinato allora ha vinto il banco
}

void tre_giocatori()
{
  int b;
  int max = round(log2(M));                     // Dichiaro max il numero massimo di tentativi che equivale al logaritmo in base 2 di M

  printf("Numero segreto:");

  while(scanf("%d", &b) != 1 || b > M)         // Chiedo al banco di inserire un numero segreto
  {
    scanf("%*[^\n]%*c");
  }
  printf(" Indovina il numero!\n");
  int num;

  for (int i = 0; i < max; i++) {              // Eseguo un ciclo che va da 0 a max-1 tentativi che serve per effettuare i max tentativi

    printf("Tentativo numero %d:", i+1);

    while(scanf("%d", &num) != 1 || num > M)
    {
      scanf("%*[^\n]%*c");
    }

    if (num < b)                                // Se il numero inserito dal giocatore risulta minore del numero segreto allora suggerisco al giocatore che il suo numero è piu basso
    {
      printf(" Troppo basso\n");
    }
    else if (num > b)                           // Se il numero inserito dal giocatore risulta maggiore del numero segreto allora suggerisco al giocatore che il suo numero è piu grande
    {
      printf(" Troppo alto\n");
    }
    else if (num == b && i%2 == 0)              // Se il numero inserito dal giocatore è uguale al numero segreto e il numero del tentativo è pari, avendo iniziato il giocatore 1, il giocatore 1 ha vinto
    {
      printf(" Ha vinto il giocatore n. 1\n");
      return;
    }
    else if (num == b && i % 2 != 0)            // Se il numero inserito dal giocatore è uguale al numero segreto e il numero del tentativo è dispari, avendo iniziato per secondo il giocatore 2, il giocatore 2 ha vinto
    {
      printf(" Ha vinto il giocatore n. 2\n");
      return;
    }
  }
  printf("Ha vinto il banco!\n");             // Se si raggiunge il numero massimo di tentativi senza aver indovinato allora ha vinto il banco
}


void esci()
{
  return;                                    // Ritorno alla funzione chiamante
}
