#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct evento{            // Definisco una struct che mi servirà per contenere le informazioni di tutti gli eventi atmosferici presi in input
  unsigned int codice;
  int x;
  int y;
  int z;
  int gg;
  int mm;
  int aa;
  int ore;
  int minuti;
  int events;
  int mark;
  int row;
  struct evento *next;
}Evento;

typedef Evento* eventoPtr;

void insert (eventoPtr *lPtr,int ev, int x, int y, int z, int g, int m, int a, int h, int mi,int c);  // Funzione per l'inserimento in lista dei dati di ogni evento letto da file
void print_list(eventoPtr lPtr); // Funzione per la stampa ordinata
void astral_distance(eventoPtr lPtr, int d); // Funzione per il calcolo della distanza astrale tra gli eventi
eventoPtr order_events(eventoPtr *lPtr);  // Funzione di ordinamento secondo il codice degli eventi
eventoPtr order_date(eventoPtr *lPtr);  // Funzione di ordinamento secondo la data dell'evento
void check_position(eventoPtr lPtr);  // Funzione per il controllo della posizione degli eventi
void check_code(eventoPtr lPtr);  // Funzione per il controllo di eventuali codici di evento duplicati


int main(int argc, char *argv[2])
{
  FILE *fptr;
  fptr = fopen(argv[1], "r");         // Apro il primo file passato dal linea di comando in modalità lettura, contenente le informazioni di ogni evento
  if(fptr == NULL)
  {
    puts("Impossibile aprire il file.");  // In caso di errore nell'apertura del file il programma termina
    exit(EXIT_FAILURE);
  }

  Evento *lista = NULL;                 // Dichiaro un puntatore alla struct di tipo Evento e la inizializzo a NULL

  int codice,x,y,z,gg,mm,aa,ore,min;
  int counter = 1;
  while(!feof(fptr)){                   // Finchè non si raggiunge la fine del file (al carattere speciale EOF) leggo dal file CSV le informazioni degli eventi e ne controllo la correttezza
    if(fscanf(fptr, "%d,%d,%d,%d,%d/%d/%d,%d:%d\n", &codice, &x, &y, &z, &gg, &mm, &aa, &ore, &min)<9
       || codice < 0 || gg < 0 || gg > 31 || mm < 0 || mm > 12 || aa < 0 || ore < 0 || ore > 23 || min < 0 || min > 59)
    {
      printf("Ops. Il file non sembra essere formattato bene (riga %d).\n", counter); // In caso di errore nella formattazione del file stampo un errore specificando la prima riga in cui vi è un errore ed esco dal programma
      return 0;
    }
    else
    {
      insert(&lista,codice,x,y,z,gg,mm,aa,ore,min,counter); // Se i dati degli eventi sono corretti allora chiamo la funzione di inserimento in modo da inserire in lista ogni evento con i propri dati
      counter++;    // Utilizzo un contatore per contare le righe in modo da poter specificare in caso di errore, di quale riga si tratta
    }
  }

  int D;
  D=atoi(argv[2]);  // D è il raggio astrale che viene passato da linea di comando, essendo quindi una stringa passata come argomento al main utilizziamo la funzione atoi per convertirla in un intero
  check_code(lista); // Chiamo la funzione che controlla che i codici degli eventi siano tutti distinti
  astral_distance(lista,D); // Chiamo la funzione che effettua il calcolo della distanza astrale tra gli eventi
  order_date(&lista); // Chiamo la funzione di ordinamento per data del primo evento incontrato nella data zona
  order_events(&lista); // Chiamo la funzione di ordinamento per codice di evento in ordine decrescente
  check_position(lista);
  print_list(lista);  // Stampo le zone con la maggior frequenza di eventi  insieme alla corrispondente frequenza degli eventi

}


void insert (eventoPtr *lPtr,int ev, int x, int y, int z, int g, int m, int a, int h, int mi, int c)
{
  eventoPtr newPtr = malloc(sizeof(Evento));  // Appena viene chiamata la funzione insert siamo sicuri che i dati letti nella prima riga del file sono ben formattati, allochiamo quindi la memoria per una nuova struct (nodo)
  if (newPtr != NULL)                         // Se l'allocazione va a buon fine, il puntatore restituito da malloc sarà diverso da NULL(sarà un puntatore void), quindi c'è spazio in memoria
  {
    newPtr->codice = ev;                      // Inserisco i dati dell'evento letto dal file nella corrispondente struct o nodo della lista
    newPtr->x = x;
    newPtr->y = y;
    newPtr->z = z;
    newPtr->gg = g;
    newPtr->mm = m;
    newPtr->aa = a;
    newPtr->ore = h;
    newPtr->minuti = mi;
    newPtr->events = 1;
    newPtr->mark = 0;
    newPtr->row = c;
    newPtr->next = *lPtr;                 // Il puntatore del nuovo nodo inserito punterà a ciò che veniva puntato dalla testa, perchè abbiamo eseguito un inserimento in testa

    *lPtr = newPtr;                       // Ho effettuato un inserimento in testa, quindi il puntatore alla lista adesso punterà al nuovo nodo appena inserito in cima alla lista
  }
  else puts("Memoria esaurita");          // Se l'allocazione di memoria non va buon fine allora significa che non abbiamo piu memoria per allocare
}


void print_list(eventoPtr lPtr)
{
  eventoPtr current = lPtr;
  if (current == NULL) puts("Lista vuota");
  else
  {
    printf("Coordinate Zona      Numero eventi       \n");
    while(current != NULL)
    {
      if(current->mark != 1)
          printf("( %2d,  %2d,  %2d)      %d\n", current->x,current->y,current->z, current->events);    // Eseguo la stampa scorrendo la lista, stampo le coordinate degli eventi e il numero di eventi che ci sono nel raggio di quella posizione nello spazio
      current = current->next;    // Scorro la lista passando al nodo successivo
    }
  }
}

void astral_distance(eventoPtr lPtr, int d)
{
  eventoPtr current = lPtr;                 // Dichiaro un puntatore di tipo Evento che prende il valore della testa e lo utilizzo come cursore
  eventoPtr success = current->next;        // Dichiaro un puntatore di tipo Evento che punta al nodo successivo a current

  while(success != NULL)                  // Finchè il puntatore successivo è diverso da NULL
  {
    if(sqrt(pow(current->x - success->x,2)+pow(current->y - success->y,2)+pow(current->z - success->z,2)) <= d) // Devo calcolare la distanza nello spazio tridimensionale di un evento con tutti i suoi successivi e/o precedenti,
    {                                                                                                           // se tale distanza è minore o uguale a D che era il raggio allora aumento la variabile evento di 1 in entrambi gli eventi di cui sto facendo il confronto
      current->events++;
      success->events++;
    }
    success = success->next;        // Condizione di scorrimento della lista, success punta adesso al nodo successivo
    if(success == NULL)             // Se il puntatore success arriva alla fine della lista, il puntatore current scorre di una posizione passando al suo nodo successivo e il puntatore success punta al nodo successivo di quello puntato da current
    {
      current = current->next;      // Quando current non sarà piu il primo nodo della lista, se success arriva a null in fondo alla lista esso deve tornare in cima affinchè avvengano tutti i confronti tra i nodi
      success = current->next;
    }
  }
}

eventoPtr order_events(eventoPtr *lPtr)
{
  if((*lPtr) == NULL || (*lPtr)->next == NULL) return *lPtr;      // Se la lista è vuota o contiene un solo elemento allora non c'è da ordinare e la funzione riporta la testa

  eventoPtr temp;
  int controllo;

  do {
    controllo = 0;
    if((*lPtr)->events < ((*lPtr)->next)->events)       // Se il numero di eventi nel primo nodo cioè nella testa è minore del numero di eventi del nodo successivo allora avviene lo swap
    {
      controllo = 1;
      temp = (*lPtr)->next;
      (*lPtr)->next = temp->next;
      temp->next = *lPtr;
      *lPtr = temp;
    }

    for(temp = *lPtr; (temp->next)->next != NULL; temp = temp->next)    // Eseguo un ciclo for che come indice ha un puntatore temp che parte dalla testa e scorre la lista, in caso si verifichi la condizione dell'if cioà il numero di evento del nodo successivo è maggiore del nodo corrente allora si effettua lo swap tra i nodi
    {
      if((temp->next)->events < ((temp->next)->next)->events)           // in questo modo ordino la lista per numero di eventi
      {
        if(controllo == 0)
            controllo = 1;
        eventoPtr swap = (temp->next)->next;                            // Dichiaro un puntatore temporaneo che serve per effettuare lo scambio
        (temp->next)->next = swap->next;
        swap->next = temp->next;
        temp->next = swap;
      }
    }
  }
  while(controllo);
 return *lPtr;
}

eventoPtr order_date (eventoPtr *lPtr)
{
  if((*lPtr) == NULL || (*lPtr)->next == NULL) return *lPtr;    // Se la lista è vuota o contiene solo un nodo allora ritorno il puntatore alla lista perchè niente deve essere ordinato

  eventoPtr temp;
  int controllo;

  do {
    controllo = 0;
    if((*lPtr)->aa > ((*lPtr)->next)->aa || (*lPtr)->aa == ((*lPtr)->next)->aa && (*lPtr)->mm > ((*lPtr)->next)->mm         // Effettuo i controlli sulla data tra il primo nodo, cioè alla testa e il suo successivo, confrontando anno, mese e giorno, il primo controllo è tra gli anni delle due date, il secondo è in caso di anno uguale,
        || (*lPtr)->aa == ((*lPtr)->next)->aa && (*lPtr)->mm == ((*lPtr)->next)->mm && (*lPtr)->gg > ((*lPtr)->next)->gg)   // e si controlla il mese, in caso di anno e mesi uguali si controlla il giorno, e poi al verificarsi di una di queste condizioni si effettua lo swap e si scambiano
    {
      //controllo = 1;
      temp = (*lPtr)->next;       // Swap con l'appoggio di una variabile temporanea
      (*lPtr)->next = temp->next;
      temp->next = *lPtr;
      *lPtr = temp;
    }

    for(temp = *lPtr; (temp->next)->next != NULL; temp = temp->next)      // Ciclo for per scorrere l'intera lista ed effettuare i confronti per l'ordinamento
    {
      if((temp->next)->aa > ((temp->next)->next)->aa || (temp->next)->aa == ((temp->next)->next)->aa && ((temp->next)->mm > ((temp->next)->next)->mm)         // Stessi controlli sulla data descritti precedentemente
          || (temp->next)->aa == ((temp->next)->next)->aa && (temp->next)->mm == ((temp->next)->next)->mm && ((temp->next)->gg > ((temp->next)->next)->gg))
      {
        if(controllo == 0)
            controllo = 1;
        eventoPtr swap = (temp->next)->next;      // Swap nel caso in cui si dovesse verificare una delle condizioni precedenti
        (temp->next)->next = swap->next;
        swap->next = temp->next;
        temp->next = swap;
      }
    }
  }
  while(controllo);
 return *lPtr;
}

void check_position(eventoPtr lPtr)
{
  eventoPtr previous = lPtr;              // Dichiaro due puntatori che serviranno da cursori per scorrere la lista
  eventoPtr current = previous->next;

  while(current != NULL)
  {
    if(previous->x == current->x && previous->y == current->y && previous->z == current->z) // Controllo se ci sono eventi dal codice diverso ma nella stessa posizione nello spazio cioè con le stesse coordinate
    {
      previous->mark = 1;   // In tal caso pongo a 1 la variabile mark di uno dei due nodi, ciò mi servirà per la stampa perchè in questo modo non stamperò duplicati, se piu eventi hanno la stessa posizione ne stamperò una soltanto
    }
    current = current->next;    // Condizione di scorrimento
    if(current == NULL)         // Devo effettuare il confronto di ogni nodo per ogni nodo quindi nel caso in cui previous non sia piu alla testa, current deve poter tornare in cima quando arriverà alla fine della lista in modo da non saltare un confronto
    {
      previous = previous->next;
      current = previous->next;
    }
  }
}

void check_code(eventoPtr lPtr)
{
  eventoPtr previous = lPtr;              // Dichiaro due puntatori che faranno da cursori per scorrere la lista
  eventoPtr current = previous->next;

  while(current != NULL)
  {
    if(previous->codice == current->codice)       // Se il codice del nodo puntato da previous è uguale al codice del nodo puntato da current allora vi è un conflitto di codici e stampo un errore evidenziando le righe in cui avviene tale errore
    {
      printf("Errore: l'evento alla riga %d ha lo stesso codice di quello alla riga %d\n", previous->row, current->row);
      exit(EXIT_FAILURE);
    }
    current = current->next;
    if(current == NULL)               // I codici degli eventi devono essere controllati tutti tra di loro, quindi previous non punterà piu alla testa ma sarà al suo successivo, se current arriva alla fine della lista deve ripartire dalla cima per far in modo di aver controllato il nodo corrente con tutti i restanti nodi della lista
    {
      previous = previous->next;
      current = previous->next;
    }
  }
}
