#include <stdio.h>

int main() {

    int A,B,C = 0;

    scanf("%d", &A);
    scanf("%d", &B);
    scanf("%d", &C);

    if (A > B && A > C)
    {
        printf("%d", A);
    }

    else if (B > A && B > C)
    {
        printf("%d", B);
    }

    else
    {
        printf("%d", C);
    }

    return 0;
}