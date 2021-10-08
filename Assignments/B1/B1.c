#include <stdio.h>
#include <stdlib.h>

typedef struct numero                       // Definisco una struct che mi serve per mantenere i dati riguardo il valore, la posizione e l'occorrenza di ogni numero nella matrice
{
  int valore;
  int riga;
  int colonna;
  int occorrenza;
  char flag;
}Valore;

int numOfLines(FILE*filePtr);               // Conta il numero di linee nel file, dato che determinerà la dimensione della matrice
int numOfOcc(int **matr, int dim);          // Conta il numero di valori contigui nella matrice
int compare(const void *a, const void *b);  // Funzione "compare" necessaria per l'ordinamento e l'esecuzione della funzione qsort, contiene i criteri secondo quali viene eseguito l'ordinamento


int main(int argc, char *argv[1])
{
  FILE *fPtr;
  fPtr = fopen(argv[1], "r");             // Apro il file passato esternamente da linea di comando che contiene la matrice

  if( fPtr == NULL )
      return 1;

  int N = numOfLines(fPtr);             // Determino la dimensione della matrice presente nel file chiamando la funzione che conta il numero di linee della matrice
  if(N == 0)
  {
    printf("File non valido.\n");       // Se il valore restituito dalla funzione di conteggio delle linee della matrice è uguale a 0 allora il file non è valido e il programma finisce
    return 0;
  }
  char eol;

  int **matrix = malloc(N*sizeof(int*));   // Creo ed alloco un array di puntatori ad array
  for (int i = 0; i < N; i++) {
    matrix[i] = malloc(N*sizeof(int));     // Per ogni array alloco la memoria per ogni elemento
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      fscanf(fPtr,"%d", &matrix[i][j]);   // Leggo i valori della matrice dal file e li inserisco nella matrice che ho allocato in memoria
    }
    fscanf(fPtr, "%c", &eol);
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){                 // Stampo a video la matrice letta dal file
      printf("%d ",matrix[i][j]);
    }
    putc('\n', stdout);
  }


  printf("Inserire M: \n");                     // Chiedo all'utente di inserire un valore M che rappresenta il minimo numero di occorrenze
  int m;
  while(scanf("%d", &m) != 1 || m > N || m < 1)
  {
    printf("Errore. Valore non valido\n");      // In caso di input errato, informo l'utente dell'errore e chiedo di inserire nuovamente un numero
    scanf("%*[^\n]%*c");
  }
  int occ = numOfOcc(matrix,N);           // Conto il numero di valori contigui chiamando la funzione in modo da aver un numero preciso di struct nell'array di struct
  Valore *arr;                            // Dichiaro un puntatore di tipo Valore che equivale alla struct definita precedentemente
  arr = malloc(occ*sizeof(Valore));       // Alloco la memoria per gli elementi di tipo struct dell'array di struct

  for (int i = 0; i < occ; i++) {
    arr[i].occorrenza = 1;                // Setto le occorrenze dell'array di struct a 1 perchè ogni valore ha occorrenza 1 contando se stesso
  }

  int k = 0;

  for (int i = 0; i < N; i++) {         // Scorro le righe per cercare le occorrenze e aumento i valori corrispondenti
    int colonna = 0;
    for (int j = 0; j < N-1; j++)
    {
      if(matrix[i][j] == matrix[i][j+1])    // Se il valore della matrice in riga i e colonna j è uguale al valore nella stessa riga ma della colonna successiva allora aggiorno i dati della struct
      {
        arr[k].valore = matrix[i][j];   // Salvo il valore nella struct
        arr[k].occorrenza++;            // Aumento il numero di occorrenze
        arr[k].riga = i;                // Salvo l'indice della riga in cui ho trovato tale occorrenza del dato valore
        arr[k].colonna = colonna;       // Salvo l'indice della colonna in cui ho trovato tale occorrenza
        arr[k].flag = 1;                // Pongo il valore flag a 1 che mi servirà successivamente per evidenziare se l'occorrenza si trova in riga o in colonna, in questo caso siamo in un'occorrenza in riga
      }
      else
      {
        colonna += arr[k].occorrenza;     // se ho trovato delle occorrenze, le colonne che hanno l'occorrenza le salto e non le controllo, passando alla colonna successiva all'ultima occorrenza
        if(arr[k].occorrenza<2)           // Se l'occorrenza di un numero è minore di 2 allora non scorro l'array, perchè non aggiungo una nuova struct essendo l'occorrenza minore di 2
            k--;
        if(j!=N-2)
            k++;
      }
    }
    k++;
  }

  for (int i = 0; i < N; i++) {                 // Scorro le colonne per cercare le occorrenze e aggiorno i valori corrispondenti
    int riga = 0;
    for (int j = 0; j < N-1; j++) {
      if(matrix[j][i] == matrix[j+1][i])
      {
        arr[k].valore = matrix[j][i];        // Salvo il valore nella struct
        arr[k].occorrenza++;                 // Aumento il numero di occorrenze
        arr[k].riga = riga;                  // Salvo l'indice della riga in cui ho trovato l'occorrenza
        arr[k].colonna = i;                  // Salvo l'indice della colonna in cui ho trovato l'occorrenza
        arr[k].flag = 0;                     // Pongo il valore flag a 0 che mi servirà successivamente per evidenziare se l'occorrenza si trova in riga o in colonna, in questo cadso siamo in un'occorrenza in colonna
      }
      else
      {
        riga += arr[k].occorrenza;
        if(arr[k].occorrenza<2)
            k--;
        if(j!=N-2)
            k++;
      }
    }
    k++;
  }

  qsort(arr,occ,sizeof(Valore), compare); // Chiamo la funzione di ordinamento

  for (size_t k = 0; k < occ; k++) {
    if (arr[k].occorrenza >= m && arr[k].flag == 1)     // Scorro l'array di struct con un ciclo for, se l'occorrenza della struct in questione è maggiore o uguale al numero di occorrenze minimo scelto da tastiera e la flag è 1 quindi si riferisce alle occorrenze in riga, allora stampo
        printf("Ci sono %d occorrenze consecutive di %d in riga %d a partire della colonna %d\n", arr[k].occorrenza, arr[k].valore, arr[k].riga, arr[k].colonna);
    if (arr[k].occorrenza >= m && arr[k].flag == 0)   // Se l'occorrenza della struct in questione è maggiore o uguale al numero di occorrenze minimo scelto da tastiera e la flag è 0 quindi si riferisce alle occorrenze in colonna, allora stampo
        printf("Ci sono %d occorrenze consecutive di %d in colonna %d a partire della riga %d\n", arr[k].occorrenza, arr[k].valore, arr[k].colonna, arr[k].riga);
  }

  free(arr);      // Libero la memoria precedentemente allocata per l'array di struct
  fclose(fPtr);
}

int compare(const void *a, const void *b)
{
  Valore s1 = *(Valore*)a;
  Valore s2 = *(Valore*)b;


  if(s1.occorrenza < s2.occorrenza || (s1.occorrenza == s2.occorrenza && (s1.flag > s2.flag || s1.flag < s2.flag)) || // Condizioni di ordinamento, per l'ordinamento decrescente delle occorrenze confronto le occorrenze
     s1.occorrenza == s2.occorrenza && s1.flag == s2.flag && ((s1.colonna > s2.colonna || s1.colonna < s2.colonna) || // tra le struct, in caso di occorrenze uguali do la precedenza alle colonne e poi le righe sempre in
     (s1.riga > s2.riga || s1.riga < s2.riga)))                                                                       // ordine decrescente del numero di riga/colonna. Le occorrenze sulla stessa riga o colonna le ordino in modo crescente
    return 1;                                                                                                         // della posizione di partenza

  if(s1.occorrenza > s2.occorrenza)
   return -1;

  return 0;

}


int numOfLines(FILE*filePtr)
{
  int counter,val,r;

  while(!feof(filePtr))                     // Finchè non arrivo al carattere speciale EOF che indica la fine del file, leggo gli interi decimali della matrice in modo da poter aumentare un contatore che mi servirà per contare quanti elementi ci sono in matrice
  {
    fscanf(filePtr, "%d ", &val);
    counter++;
  }

  if(counter < 16) return 0;              // Le matrici devono essere almeno 4x4  quindi in caso di un numero di elementi minore a 16 la funzione riporta 0

  for (int i = 1; i <= counter/4; i++) {        // Avendo contato il numero di elementi totali nella matrice con counter, se divido tale numero per un numero qualsiasi i ed ottengo il numero stesso allora la matrice è qaudrata
    if((float)counter/i == i && i >=4)
    {
      r = i;
      break;
    }
    else if(i == counter/4)
      return 0;
  }

  rewind(filePtr);
  return r;
}

int numOfOcc(int **matr, int dim)
{
  int occorrenza;

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim-1; j++) {
      if(matr[i][j] == matr[i][j+1])            // Se trovo un'occorrenza di 2 numeri aumento il contatore delle sequenze
      {
        occorrenza++;
        if(j!=0 && matr[i][j]==matr[i][j-1])      // Nel caso in cui avessi un'occorrenza di un valore per piu di 2 volte allora io avrò bisogno di 1 sola per rappresentarle tutte
        {
            occorrenza--;
        }
      }

      if(matr[j][i] == matr[j+1][i])
      {
        occorrenza++;
        if(j != 0 && matr[j][i] == matr[j-1][i])
        {
          occorrenza--;
        }
      }
    }
  }

return occorrenza;

}
