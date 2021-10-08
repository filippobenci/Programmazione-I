#include <stdio.h>

double approx_pi (int n);

int main() {

    int n;

    while(scanf("%d", &n) != 1 || n < 0)
        {
            printf("Inserisci un intero positivo.\n");
            scanf("%*[^\n]%*c");
        }

    printf("%.6f\n", approx_pi(n));

    return 0;
}

double approx_pi (int n)
{

}