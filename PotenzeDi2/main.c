#include <stdio.h>

long int pot2 (int n);

int main() {

    int x;

    while(scanf("%d", &x) != 1 || x < 0)
        {
            scanf("%*[^\n]%*c");
            printf("Errore. Inserisci un numero intero positivo\n");
        }

    printf("%ld", pot2(x));

}

    long int pot2 (int n)
{
    if(n == 1)
    {
        return 2;
    }
    else
        {
         return 2*(pot2(n-1));
        }
}