#include <stdio.h>

int main() {

    float A = 0;
    float sum = 0;

    for(int i = 1; i <= 3; i++)
    {
        scanf("%f", &A);
        sum = sum + A;
    }

    printf("%.3f", sum/3);



    return 0;
}