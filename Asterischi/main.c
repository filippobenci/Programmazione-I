#include <stdio.h>

void asterischi (int x);

int main() {
    int n;
    while(scanf("%d", &n) != 1 || n < 0)
    {
        printf("Incorretto. Inserisci un intero positivo.\n");
        scanf("%*[^\n]%*c");
    }

    asterischi(n);
}

void asterischi(int x)
{
    for( int i = 1; i <= x; i++)
    {
        printf("%c", '*');

        if( i == x)
        {
            printf("\n");
            asterischi(x-2);
        }
    }
}