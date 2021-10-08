#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prodotto{            // Definisco la struct per contenere i dati di ogni prodotto
  int codice;
  char name[20];
  int prezzo;
  int quantita;
  struct prodotto *next;
}Product;

typedef Product* productPtr;

void change_quantity(productPtr lPtr);    // Funzione per la modifica della quantita di un prodotto
void change_price(productPtr lPtr);       // Funzione per la modifica del prezzo di un prodotto
void insert_new(productPtr *lPtr);        // Funzione per inserire in lista un nuovo prodotto
void insert_list(productPtr *lPtr,int c, char n[], int p);  // Funzione per inserire in lista leggendo dal file csv
void delete_existing(productPtr *lPtr);   // Funzione per eliminare un prodotto dalla lista
void search_product(productPtr lPtr);     // Funzione per cercare un prodotto tramite il codice
void print_products(productPtr lPtr);     // Funzione per la stampa della lista
void esci(FILE *filePtr2, FILE *filePtr3, productPtr lPtr); // Funzione per l'uscita dal programma con scrittura sui file
void stampa(productPtr lPtr);   // Funzione per la stampa del magazzino

int soglia = 10;      // Definisco un valore di soglia (che riguarda la quantita) e lo inizializzo di default a 10

int main(int argc, char*argv[3])
{
  srand(10);                    // Il seme dei numeri pseudocasuali è 10
  FILE *fPtr;
  fPtr = fopen(argv[1], "r");     // Apro il file csv passato da linea di comando, in modalità di lettura
  if(fPtr == NULL)
  {
    puts("Impossibile aprire il file.\n");    // Se l'apertura del file non va a buon fine stampo un errore ed esco dal programma
    exit(EXIT_FAILURE);
  }
  FILE *fPtr2;
  fPtr2 = fopen(argv[2],"w");         // Apro il file di testo passato da linea di comando, in modalità scrittura
  if(fPtr2 == NULL)
  {
    puts("Impossibile aprire il file.\n");    // Se l'apertura del file non va a buon fine stampo un errore ed esco dal programma
    exit(EXIT_FAILURE);
  }
  FILE *fPtr3;
  fPtr3 = fopen(argv[3],"w");         // Apro il file bin passato da linea di comando, in modalità di scrittura
  if(fPtr3 == NULL)
  {
    puts("Impossibile aprire il file.\n");    // Se l'apertura del file non va a buon fine stampo un errore ed esco dal programma
    exit(EXIT_FAILURE);
  }


 Product *lista = NULL;       // Dichiaro un puntatore alla lista inizializzato a NULL
 int codice, prezzo;          // Dichiaro le variabile che utilizzo per leggere dal file
 char nome[100];
 while(!feof(fPtr))           // Eseguo un ciclo fino alla fine del file
   {
     if(fscanf(fPtr, "%d,%[^,],%d\n", &codice, nome, &prezzo) < 3 || codice < 0 || prezzo <= 0)   // Controllo che ogni riga del file (che contiene i dati di ogni prodotto) sia formattata bene, in caso di errore stampo un avviso ed esco dal programma
     {
       printf("Ops. Il file non sembra essere formattato bene.\n");
       exit(EXIT_FAILURE);
     }
     insert_list(&lista,codice,nome,prezzo);      // Se il controllo va a buon fine allora chiamo la funzione di inserimento in lista, in modo da creare un nuovo nodo con i dati appena letti dal file
   }
 printf("Prodotti presenti nel magazzino:\n\n");
 stampa(lista); // Stampo il magazzino
 int scelta;

 void(*f[3])(productPtr)={change_quantity,change_price,search_product};   // Dichiaro l'array di puntatori a funzioni, alle quali passo la lista

 do{
   printf("Scegliere un’opzione: \n1 - Variazione della quantità di un prodotto;\n2 - Variazione del prezzo di un prodotto;\n3 - Inserimento di un nuovo prodotto;\n4 - Eliminazione di un prodotto;\n5 - Ricerca di un prodotto;\n6 - Stampa prodotti sotto la soglia;\n7 - Esci:\n");
   while(scanf("%d", &scelta) != 1 || scelta <= 0 || scelta > 8)      // Stampo il menu testuale che indica le operazioni possibili e chiedo all'utente di fare una scelta da tastiera
   {
     printf("Errore. Inserisci un numero intero tra 1 e 7\n");      // Se l'utente immette un numero sbagliato o un carattere stampo un avviso e chiedo di effettuare nuovamente una scelta
     while(getchar() != '\n');
   }
   if(scelta == 1 || scelta == 2)     // Se la scelta effettuata è 1 o 2 allora chiamo l'array di puntatori a funzioni passando come indice la scelta dell'utente diminuita di 1 (Perchè l'array parte da 0 come indice)
   {
     (*f[scelta-1])(lista);
   }
   if (scelta == 3) insert_new(&lista);
   if (scelta == 4) delete_existing(&lista);
   if (scelta == 5) (*f[scelta-3])(lista);        // Se la scelta effettuata è 5 allora chiamo l'array di puntatori a funzioni passando come indice la scelta dell'utente diminuita di 3 perchè la funzione 5 nell'array si trova in indice 2
   if (scelta == 6)
   {
     printf("Inserisci un valore di soglia: ");         // Se la scelta effettuata è 6 chiedo all'utente di inserire da tastiera un numero che rappresenta la soglia di quantita
     while(scanf("%d", &soglia) != 1 || soglia < 0)
     {
       printf("Errore, inserisci un valore di soglia valido: ");    // In caso di errore nell'input stampo un avviso e chiedo all'utente di inserire nuovamente un valore di soglia
       scanf("%*[^\n]%*c");
     }
     printf("Elenco dei prodotti sotto la soglia:\n\n");
     print_products(lista);       // Chiamo la funzione di stampa che stamperà la lista dei prodotti sotto la soglia scelta dall'utente (la soglia si riferisce alla quantita)
   }
   if (scelta == 7)
   {
     esci(fPtr2,fPtr3,lista);  // Chiamo la funzione di uscita alla quale passo i file su cui voglio scrivere e la lista
     exit(EXIT_SUCCESS);
   }

 }while(scelta > 0 || scelta < 8);  // Finche la scelta è tra 0 e 8 stampo il menu testuale
 fclose(fPtr);      // Chiudo i file dopo l'uscita dal ciclo while
 fclose(fPtr2);
 fclose(fPtr3);
 free(lista);     // Dealloco la memoria della lista 
}

void insert_list(productPtr *lPtr,int c, char n[], int p)
{
  int quantita;
  productPtr current = *lPtr;       // Dichiaro un puntatore "corrente" che punta alla testa della lista
  productPtr previous = NULL;       // Dichiaro un putatore "precedente" che punta a null inizialmente
  quantita = rand() %100000;        // La quantita del prodotto deve essere un numero pseudocasuale tra 0 e 100000 con seme 10
      productPtr newPtr = malloc(sizeof(Product));      // Alloco la memoria per il nuovo nodo
      if(newPtr == NULL)
      {
        puts("Memoria esaurita.\n");      // Se la funzione malloc restituisce Null allora significa che non vi è spazio in memoria, in tal caso stampo un avviso ed esco dal programma
        exit(EXIT_FAILURE);
      }
      newPtr->codice = c;               // Nei campi del nuovo nodo inserisco i dati letti dal file e passati alla funzione
      strcpy(newPtr->name,n);
      newPtr->prezzo = p;
      newPtr->quantita = quantita;
      newPtr->next = NULL;            // Il puntatore al prossimo nodo lo inizializzo a null

      if(current == NULL)             // Se il puntatore "corrente" è null(cioè la lista è vuota), il nuovo nodo appena creato diventa il primo nodo della lista
        {
          newPtr->next = *lPtr;
          *lPtr = newPtr;
        }
      else
      {
        while(current!= NULL)       // Altrimenti scorro la lista finchè il puntatore "corrente", non arriva a null ed inserisco il nuovo nodo
        {
          previous = current;
          current = current->next;
        }
        previous->next = newPtr;
        newPtr->next = current;
      }
    }

void change_quantity (productPtr lPtr)
{
  int codice,quantita;
  printf("Inserisci il codice del prodotto: ");
  while(scanf("%d",&codice) != 1 || codice < 0)             // Chiedo all'utente di inserire da tastiera il codice del prodotto di cui vuole cambiare la quantita, in caso di errore nell'inserimento stampo un avviso e chiedo di inserire un nuovo codice
  {
    printf("Errore, codice non valido. Inserisci un nuovo codice: ");
    scanf("%*[^\n]%*c");
  }
  productPtr tmp = lPtr;      // Dichiaro un puntatore temporaneo che funzionerà da cursore per scorrere la lista
  while(tmp != NULL)          // Finchè il puntatore temporaneo non arriva alla fine della lista scorro
  {
    if(tmp->codice == codice)   // Se il codice del nodo puntato dal temporaneo è uguale al codice cercato stampo i dettagli del prodotto e chiedo all'utente di modificare la quantita
    {
      printf("Dettagli prodotto ricercato:\n\n%d\t%s\t%d\t%d\n\n",tmp->codice, tmp->name, tmp->prezzo, tmp->quantita);
      printf("Modifica la quantita': ");
      while (scanf("%d", &quantita) != 1 || quantita < 0)
      {
        printf("Errore, quantita non valida.\n");
        scanf("%*[^\n]%*c");
      }
      tmp->quantita = quantita; // Cambio il valore della quantità nel nodo con il nuovo valore inserito precedentemente
      printf("Dettagli prodotto aggiornati:\n\n%d\t%s\t%d\t%d\n\n",tmp->codice, tmp->name, tmp->prezzo, tmp->quantita); // Stampo i dettagli del prodotto aggiornati
      return;
    }
    tmp = tmp->next;  // Condizione di scorrimento della lista, da un nodo al suo successivo
  }
  printf("Errore, codice prodotto non trovato.\n");   // Se il codice del prodotto non è presente nella lista stampo un errore
}

void change_price (productPtr lPtr)
{
  int codice,prezzo;
  printf("Inserisci il codice del prodotto: ");
  while(scanf("%d", &codice) != 1 || codice < 0)          // Chiedo all'utente di inserire il codice del prodotto del quale vuole cambiare il prezzo, in caso di errore stampo un avviso
  {
    printf("Errore, codice non valido. Inserisci un nuovo codice: ");
    scanf("%*[^\n]%*c");
  }

  productPtr tmp = lPtr;    // Dichiaro un puntatore temporaneo necessario per scorrere la lista
  while(tmp != NULL)
  {
    if(tmp->codice == codice)         // Quando trovo il codice ricercato stampo i dettagli del prodotto, chiedo all'utente di inserire un nuovo prezzo e stampo i dettagli del prodotto aggiornati
    {
      printf("Dettagli prodotto ricercato:\n\n%d\t%s\t%d\t%d\n\n",tmp->codice, tmp->name, tmp->prezzo, tmp->quantita);
      printf("Modifica il prezzo: ");
      while (scanf("%d", &prezzo) != 1 || prezzo < 0)
      {
        printf("Errore, prezzo non valido.\n");
        scanf("%*[^\n]%*c");
      }
      tmp->prezzo = prezzo; // Aggiorno il valore del prezzo nel nodo
      printf("Dettagli prodotto aggiornati:\n%d\t%s\t%d\t%d\n\n",tmp->codice, tmp->name, tmp->prezzo, tmp->quantita);
      return;
    }
    tmp = tmp->next;    // Condizione di scorrimento della lista
  }
  printf("Errore, codice prodotto non trovato.\n");
}

void insert_new (productPtr *lPtr)
{
  int codice, prezzo, quantita;     // Dichiaro le variabili per i dettagli del nuovo prodotto da inserire
  char nome[15];
  productPtr current = *lPtr;       // Dichiaro un puntatore "corrente" e lo inizializzo alla testa della lista
  productPtr previous = NULL;       // Dichiaro un puntatore "precedente" e lo inizializzo a null
  quantita = rand () % 100000;      // Inizializzo la quantita con un numero pseudocasuale

  printf("Inserisci il codice del nuovo prodotto: ");
  while(scanf("%d", &codice) != 1 || codice < 0)                        // Chiedo all'utente di inserire i dettagli del prodotto, quindi codice, nome e prezzo
  {
    printf("Errore, codice non valido. Inserisci un nuovo codice: ");
    scanf("%*[^\n]%*c");
  }
  printf("Inserisci il nome del nuovo prodotto: ");
  scanf("%s", nome);
  printf("Inserisci il prezzo del nuovo prodotto: ");
  while(scanf("%d", &prezzo) != 1 || prezzo < 0)
  {
    printf("Errore, prezzo non valido. Inserisci un nuovo prezzo: ");
    scanf("%*[^\n]%*c");
  }
  printf("Dettagli del nuovo prodotto inserito:\n\n%d\t%s\t%d\t%d\n\n",codice,nome,prezzo,quantita);


  productPtr newPtr = malloc(sizeof(Product));      // Alloco la memoria per il nuovo nodo del nuovo prodotto
  if(newPtr == NULL)
  {
    puts("Memoria esaurita.\n");
    exit(EXIT_FAILURE);
  }
  newPtr->codice = codice;      // Inserisco nella struct (nodo) i valori inseriti dall'utente
  strcpy(newPtr->name,nome);
  newPtr->prezzo = prezzo;
  newPtr->quantita = quantita;
  newPtr->next = NULL;

  if(*lPtr == NULL)
    {
      newPtr->next = *lPtr;         // Se la lista è vuota, il nodo appena creato diventa il primo nodo della testa
      *lPtr = newPtr;
    }
  else
  {
    while(current != NULL && current->codice <= codice)     // Se la lista non è vuota faccio un inserimento ordinato in base al codice del nuovo prodotto e quelli già presenti nella lista
    {
      if(current->codice == codice)                           // Se il codice inserito da tastiera è gia presente nella lista, allora non posso inserire il nuovo prodotto
      {
        printf("Il codice e' gia' presente in magazzino\n\n");
        return;
      }
      previous = current;
      current = current->next;
    }
    previous->next = newPtr;
    newPtr->next = current;
  }
}

void delete_existing(productPtr *lPtr)
{
  int codice;
  printf("Inserisci il codice del prodotto che vuoi eliminare: ");          // Chiedo all'utente di inserire il codice del prodotto che vuole eliminare
  while(scanf("%d", &codice) != 1 || codice < 0)
  {
    printf("Errore, codice non valido. Inserisci un nuovo codice: ");
    scanf("%*[^\n]%*c");
  }

  if((*lPtr)->codice == codice)           // Se il codice inserito è uguale al primo nodo della lista cioè alla testa allora elimino tale nodo e la testa diventa il nodo successivo a quello eliminato
  {
    productPtr temp = *lPtr;
    *lPtr = (*lPtr)->next;
    printf("Dettagli prodotto eliminato:\n\n%d\t%s\t%d\t%d\n\n", temp->codice, temp->name, temp->prezzo, temp->quantita);
    free(temp);

  }
  else
  {
    productPtr previous = *lPtr;                        // Se il codice non è nel primo nodo allora scorro la lista alla ricerda del nodo
    productPtr current = (*lPtr)->next;
    while (current != NULL && current->codice != codice)
    {
      previous = current;
      current = current->next;
    }
    if(current != NULL)         // Appena trovo il nodo contenente il codice ricercato lo elimino e stampo i dettagli del prodotto eliminato
    {
      productPtr temp = current;
      previous->next = current->next;
      printf("Dettagli prodotto eliminato:\n\n%d\t%s\t%d\t%d\n\n", temp->codice, temp->name, temp->prezzo, temp->quantita);
      free(temp);
    }
  }
  printf("Errore, codice non trovato.\n");
}

void search_product (productPtr lPtr)
{
  int codice;
  printf("Inserisci il codice del prodotto che stai cercando: ");       // Chiedo all'utente di inserire il codice del prodotto che sta cercando
  while(scanf("%d", &codice) != 1 || codice < 0)
  {
    printf("Errore, codice non valido. Inserisci un nuovo codice: ");
    scanf("%*[^\n]%*c");
  }

  productPtr temp = lPtr;     // Puntatore che fa da cursore per scorrere la lista
  while(temp != NULL)
  {
    if(temp->codice == codice)        // Se il codice del nodo corrente è uguale a quello inserito dall'utente allora stampo i dettagli del prodotto ricercato altrimenti il prodotto non è presente nel magazzino
    {
      printf("Il prodotto che cercavi e':\n\n%d\t%s\t%d\t%d\n\n", temp->codice, temp->name, temp->prezzo, temp->quantita);
      return;
    }
    temp = temp->next;    // Condizione di scorrimento della lista
  }
  printf("Errore, il prodotto che stai cercando non risulta nel magazzino.\n");

}

void print_products (productPtr lPtr)
{
  productPtr current = lPtr;          // Dichiaro un puntatore che funziona da cursore per scorrere la lista
  if(current == NULL) return;
  else
  {
    print_products(current->next);      // La stampa è ricorsiva perchè quando stampiamo i prodotto sotto la soglia devono essere ordinati in modo decrescente, quindi bisogna stampare la lista partendo dal fondo
  }
  if(current->quantita < soglia) printf("%d\t%s\t%d\t%d\n", current->codice, current->name, current->prezzo, current->quantita);    // Stampo solo se la quantita del nodo corrente è minore della soglia

}

void esci(FILE *filePtr2, FILE *filePtr3, productPtr lPtr)
{
  int c = 0;    // Dichiaro due contatori che serviranno per contare i prodotti sotto la soglia e i prodotti totali
  int c2 = 0;
  productPtr temp = lPtr;   // Puntatore cursore

  while(temp != NULL)   // Scorro la lista
  {
    c++;      // Aumento il contatore che rappresenta il numero di prodotti totali
    if(temp->quantita < soglia)   // Se la quantita del nodo corrente è minore della soglia aumento il contatore che rappresenta i prodotti sotto la soglia
    {
      c2++;
      fprintf(filePtr3, "%d\t%s\t%d\n", temp->codice, temp->name,soglia-temp->quantita+1);  // Stampo sul file da Ordinare tutti i dettagli dei prodotti che devono essere ordinati, in particolare evidenziando per ogni prodotto la quantita da ordinare + 1
    }
    temp = temp->next;
  }
  fprintf(filePtr2, "%d\n%d", c,c2);    // Stampo sul file il numero di prodotti totali e il numero di prodotto sotto la soglia
  printf("Numero totale di prodotti disponibili in magazzino: %d\nNumero totale di prodotti sotto la soglia: %d\nArrivederci!\n", c, c2); // Stampo a video quanto detto nel commento precendente
}

void stampa (productPtr lPtr)
{
  productPtr current = lPtr;      // Scorro la lista e per ogni nodo stampo i dettagli dei prodotti
  while(current != NULL)
  {
    printf("%d\t%s\t%d\t%d\n", current->codice, current->name, current->prezzo, current->quantita);
    current = current->next;
  }
}
