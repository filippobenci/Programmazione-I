#include <stdio.h>
#define N 3

int verifica_array (int A[], int B[]);

int main () {

    int ArrayA[N];
    int ArrayB[N];


    for(int i = 0; i<3; i++){
        while(scanf("%d", &ArrayA[i]) != 1){
            printf("Inserisci un intero.\n");
            scanf("%*[^\n]%*c");
        }
    }
    for(int i = 0; i<3; i++){
        while(scanf("%d", &ArrayB[i]) != 1){
            printf("Inserisci un intero.\n");
            scanf("%*[^\n]%*c");
        }
    }
    printf("%s",verifica_array(ArrayA,ArrayB));
    return 0;
}

int verifica_array(int A[], int B[])
{
    int c=0;
    for(int i = 0; i<3;i++){
        for (int j=0; j<3; j++){
            if(A[i]<B[j]){
                c++;
            }

        }
        if(c==3){
            return "TRUE";
        }
        else{
            c=0;
        }
    }
    if(c==0){
        return "FALSE";
    }
}