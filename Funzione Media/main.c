#include <stdio.h>

float media (void);
int main() {

    printf("%f\n", media());

}

float media (void)
{
    int x;
    float m = 0;

    for(int i = 0; i < 10; i++ )
    {
        while(scanf("%d", &x) != 1)
        {
            scanf("%*[^\n]%*c");
            printf("Inserisci un intero.\n");
        }


    }



}