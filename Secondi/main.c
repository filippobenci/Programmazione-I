#include <stdio.h>

int main() {

    int s1;

    int s = 0;
    int m = 0;
    int h = 0;

    while(scanf("%d", &s1) < 0)
    {
        printf("Invalid input");
    }

    s = (s1%3600)%60;
    m = (s1%3600)/60;
    h = (s1/3600);

    printf("%d h %d min %d s",h,m,s);




    return 0;
}