#include <stdio.h>

void stampa_cifre (int n);
void stampa_cifre_inverso(int n);

int main() {

    int x;
    while(scanf("%d", &x) != 1 || x < 0)
        {
        scanf("%*[^\n]%*c");
        printf("Errore. Inserisci un intero positivo.\n");
        }

    stampa_cifre_inverso(x);
    stampa_cifre(x);


    return 0;

}


void stampa_cifre_inverso (int n)
{

        if(n<10)
        {
            printf("%d\n",n);
        }
        else
        {
           printf("%d\n",(n%10));
            stampa_cifre_inverso (n/10);

        }


}

void stampa_cifre (int n)
{
    if(n < 10) return;


        stampa_cifre(n / 10);
        printf("%d\n", n % 10);

}