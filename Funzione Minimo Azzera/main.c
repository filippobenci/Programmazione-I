#include <stdio.h>
#define N 10
int min_azzera (int A[]);

int main() {

    int Array[N];
    int minimo;

    for(int i = 0; i < N; i++)
    {
        scanf("%d", &Array[i]);
    }

    minimo = min_azzera(Array);

    for(int i = 0; i < N; i++)
    {
        printf("%d\n", Array[i]);
    }
    printf("%d\n", minimo);
}

int min_azzera (int A[])
{
    int min;

    for (int i = 0; i < N; i++) {

        if( min > A[i])
        {
            min = A[i];
        }

        if(i % 2 != 0 /*&& A[i] != min*/)
        {
            A[i] = 0;
        }


    }

    return min;
}