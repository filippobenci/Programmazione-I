#include <stdio.h>
#include <stdlib.h>
#define BIT 32                                  // Definisco una macro che rappresenta il numero di BIT da rappresentare per i complementi a due


int nuovo_numero(int x);
void stampa_C2(int x);
void calcola_opposto(int x);
void stampa_C2_opposto(int x);

int scelta,n;
int main()
{
  printf("Inserisci un numero intero: ");         // Il programma chiede all'utente di inserire da tastiera un numero intero su cui effettuare le operazioni

  while(scanf("%d", &n) != 1)
  {
    printf("Errore. Inserisci un numero intero.");
    scanf("%*[^\n]%*c");
  }

  void(*f[3])(int)= {stampa_C2,calcola_opposto,stampa_C2_opposto};      // Dichiaro un array di puntatori a funzioni alle quali passo il numero che ho scelto di usare nel programma e sul quale voglio effettuare i calcoli

  do{
      printf("Scegli un'opzione:\n\t1) Inserisci un nuovo numero.\n\t2) Stampa rappresentazione in complemento a due.\n\t3) Calcola opposto.\n\t4) Stampa rappresentazione in complemento a due dell'opposto.\n\t5) Esci.\nScelta: "); //Stampo il menu delle operazioni possibili
      while(scanf("%d", &scelta) != 1)      // Faccio la scelta tra quelle elencate dal menu, da tastiera
        {
          while(getchar() != '\n');
        }

      if(scelta < 5 && scelta > 1)      // Se la scelta è tra 1 e 5 allora utilizzo la scelta diminuita di 2 come indice dell'array per eseguire la funzione voluta e passo l'intero su cui voglio lavorare alla funzione che andrò a scegliere
        {
          (*f[scelta-2])(n);
        }
      if (scelta == 5)        // Se la scelta è 5 allora stampo un saluto ed esco dal programma
        {
          printf(" Bye\n");
            break;
        }
      if (scelta == 1)      // Se la scelta è 1 chiamo la funzione che mi chiederà di inserire un nuovo numero
      {
        n = nuovo_numero(n);
      }
    } while(scelta < 5 || scelta > 0);    // Condizione di guarda del ciclo "do-while"
}

int nuovo_numero(int x)   // Funzione per l'inserimento di un nuovo numero
{
  printf(" Inserisci un numero intero: ");      // Chiedo all'utente di inserire un nuovo numero
    while(scanf("%d", &x) != 1)
    {
      printf("Errore. Inserisci un numero intero.\n");    // In caso di inserimento di un carattere sbagliato, stampo un messaggio di errore e svuoto il buffer chiedendo all'utente di inserire un numero valido
      scanf("%*[^\n]%*c");
    }
  return x;
}

void stampa_C2(int x) // Funzione per la stampa del complemento a due del numero inserito
{
  int a[BIT] = {0};   // Dichiaro un array di dimensione BIT e lo inizializzo a zero, ciò servira per la rappresentazione a 2 del numero
  int temp =  x;
  int resto;
  int d = 0;

  while (temp != 0) {               // Per ottenere il complemento a due di un numero occorre fare il modulo tra il numero e 2 finchè non si arriva a 0 e conservare il valore assoluto dei resti, il risultato si ottiene leggendo il numero ottenuto dai resti al contrario
      resto = abs(temp%2);
      a[d] = resto;                 // Conservo in ogni posizione dell'array il resto ottenuto dall'operazione di modulo
      d++;
      temp /= 2;
     }

  if(x < 0)                         // Se il numero inserito inizialmente è negativo allora il complemento a due si ottiene effettuando l'operazione di modulo precedente ma a differenza di un positivo occorre invertire gli 0 con 1 e sommare 1 (somma binaria)
  {
    for (int i = BIT-1; i >= 0; i--) {      // Sostituisco gli 0 con 1 scorrendo l'array al contrario
    if(a[i] == 0)
    {
      a[i] = 1;
    }
    else a[i] = 0;
    }

    for (int j = 0; j < BIT; j++) {       // A questo punto occorre effettuare la somma binaria, sommando +1 al numero binario ottenuto precendemente, ciò serve per rappresentare il fatto che il numero è negativo, graficamente si può ovviare questa operazione semplicemente sostiuendo a tutti gli 1 con 0 e appena troviamo il primo 0 lo sostiuiamo con 1 ed esco dal ciclo
   if(a[j] == 1)
   {
     a[j] = 0;
   }
   else
   {
     a[j] = 1;
     j = BIT;
   }
  }
 }

  printf(" La rappresentazione di %d in complemento a due (MSB) è: ", x);       // Stampo il complemento a due scorrendo l'array in senso inverso
   for (int i = BIT-1; i >= 0; i--) {
     printf("%d", a[i]);
     if(i % 4 == 0)
     {
       printf(" ");
     }
   }
   printf("\n\n");

}

void stampa_C2_opposto(int x)
{
  int a[BIT] = {0};         // Inizializzo un array di lunghezza BIT a 0
  int temp =  x;
  int resto;
  int d = 0;

  while (temp != 0) {           // Calcolo nuovamente il complemento a 2 del numero stesso
      resto = abs(temp%2);
      a[d] = resto;
      d++;
      temp /= 2;
     }

  if(x > 0)                   // Questa volta se il numero è positivo allora devo ripetere l'operazione di inversione degli 0 con 1 e sommare 1, altrimenti se il numero in ingresso è negativo allora basta semplicemente fare il valore assoluto del numero stesso e calcolare il complemento a due facendo le operazioni di modulo
  {
    for (int i = BIT-1; i >= 0; i--) {
    if(a[i] == 0)
    {
      a[i] = 1;
    }
    else a[i] = 0;
    }

    for (int j = 0; j < BIT; j++) {  //
   if(a[j] == 1)
   {
     a[j] = 0;
   }
   else
   {
     a[j] = 1;
     j = BIT;
   }
  }
 }
 printf(" La rappresentazione dell'opposto di %d in complemento a due (MSB) è: ", x); // Stampo l'opposto del numero in complemento a due scorrendo in ordine inverso l'array
  for (int k = BIT-1; k >= 0 ; k--) {
    printf("%d",a[k]);
    if(k % 4 == 0)
    {
      printf(" ");
    }
  }
 printf("\n\n");
}

void calcola_opposto(int x)
{
  printf(" L'opposto di %d è %d\n",x, (-1)*x); // Calcolo l'opposto di un numero moltiplicandolo per -1
}
