#include <stdio.h>
#include <stdlib.h>

void palindroma (void);

int main(){

    palindroma();
    if ( getchar() == '\n')
    {
        printf("palindrome\n");
    }

}


void palindroma (void) {

    char c;

    c = getchar();

    if ( c == '*')
    {
        return;
    }

    palindroma();

    if ( c == getchar())
    {
        return;
    }
    else
    {
        printf("non palindrome\n");
    }


}
