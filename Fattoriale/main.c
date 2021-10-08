#include <stdio.h>

unsigned long long int fatt(int a);

int main() {

    int x;
    while (scanf("%d", &x) != 1 || x < 0)
    {
        scanf("%*[^\n]%*c");
        printf("Incorretto. Inserisci un intero positivo.\n");
    }

    printf("%llu",fatt(x));


    return 0;
}


unsigned long long int fatt(int a)
{
    if ( a == 0)
    {
        return 1;
    }
    else
    {
        return a*fatt(a-1);
    }

}