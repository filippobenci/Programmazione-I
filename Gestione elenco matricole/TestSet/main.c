#include <stdio.h>
#include <stdlib.h>

typedef struct studenti{
    int m;
    struct studenti *next;
}stud;
typedef stud* studPtr;

void add_end (studPtr* list);
void insert_tail(studPtr* list, int n);
int recLenght (studPtr list);
void recStampaInversa (studPtr list);
void deleteMultipli (studPtr *list,int m);
void recStampa(studPtr list);
void PariDispari (studPtr list, int *arr);

int main()
{
    stud* anonimi = NULL;
    add_end(&anonimi);
    int numOfSerialNumbers, multiplo;
    numOfSerialNumbers = recLenght(anonimi);
    printf("Stampa l'elenco in ordine inverso di immissione (NULL se vuota):\n");
    recStampaInversa(anonimi);
    printf("NULL \n");
    printf("Inserisci il numero richiesto:");
    scanf("%d", &multiplo);
    deleteMultipli(&anonimi,multiplo);
    printf("\nStampa l'elenco in ordine di immissione (NULL se vuota):\n");
    recStampa(anonimi);
    int pari_dispari [2];
    pari_dispari[0] = pari_dispari[1] = -1;
    PariDispari(anonimi,pari_dispari);
    printf("Dispari:%d\nPari:%d\n", pari_dispari[0],pari_dispari[1]);






}

void add_end(studPtr* list)
{
    int n;
    while(1)
    {

        if (scanf("%d",&n) != 1 || n < 0)
        {
            printf("Inserisci intero positivo o 0 per uscire\n");
            while(getchar() != '\n');
        }
        if(n == 0) break;
        studPtr temp = *list;

        if(*list == NULL)
        {
            if(n > 0)
            {
                studPtr newStud = malloc(sizeof(stud));
                newStud->m = n;
                newStud->next = *list;
                *list = newStud;
            }
        }
        else
        {
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            if(n > 0)
            {
                temp->next = malloc(sizeof(stud));
                temp = temp->next;
                temp->m = n;
                temp->next = NULL;
            }
        }
    }
}

int recLenght (studPtr list)
{
    if(list == NULL) return 0;
    else return 1 + recLenght(list->next);
}

void recStampaInversa(studPtr list)
{
    studPtr current = list;

    if(current == NULL)return;
    else recStampaInversa(current->next);
    printf("%d->",current->m);
}

void deleteMultipli (studPtr* list, int m)
{
    if(*list == NULL) return;

    if((*list)->m % m == 0)
        {
            studPtr temp = *list;
            *list = (*list)->next;
            free(temp);
        }

    studPtr previous = *list;
    studPtr current = previous->next;
    if(previous->m % m == 0)
    {
        studPtr temp = previous;
        previous = previous->next;
        free(temp);
    }

    while(current!= NULL)
    {
        if(current->m % m == 0)
        {
            studPtr temp = current;
            previous->next= current->next;
            //current = current->next->next;
            free(temp);
        }

        previous = current;
        current = current->next;
    }
}

void recStampa (studPtr list)
{
    if (list == NULL)
    {
        printf("NULL \n");
        return;
    }
    else
    {
        printf("%d->", list->m);
        recStampa(list->next);
    }
}

void PariDispari (studPtr list, int *arr)
{
    studPtr temp = list;

    while(temp != NULL)
    {
        if(temp->m % 2 != 0)
        {
            arr[0] = temp->m;
            break;
        }
        temp = temp->next;
    }

    temp = list;

    while(temp!= NULL)
    {
        if(temp->m % 2 == 0)
        {
            arr[1] = temp->m;
            break;
        }
        temp = temp->next;
    }
}
