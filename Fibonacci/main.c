#include <stdio.h>


int main() {

    int s;
    int t1 = 0;
    int t2  = 1;
    int next_term;

    while (scanf("%d", &s) != 1 || s < 0) {
        scanf("%*[^\n]%*c");
        printf("Inserire un intero positivo\n");
    }

    for(int i = 0; i <= s; i++)
    {
        printf("%d\n", t1);
        next_term = t1 + t2;
        t1 = t2;
        t2 = next_term;

        if(t1 > s)
        {
            break;
        }
    }

    return 0;
}
