#include <stdio.h>
#define R 4
#define C 3

int multipli3 (int m[][C]);
int main() {

    int matrix[R][C];

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {

            scanf("%d", &matrix[i][j]);
        }
    }

   printf("%d", multipli3(matrix));
}


int multipli3 (int m[][C])
{
  int i = 0;
  int j = 0;
  int c = -1;
  int sum = 0;
  int x =0;

  while(j < 3){
    while(i<n){
      sum= m[i][j] % 3;
      x += sum;
      i++;
    }
    if ( x == 0)
    {
      c=j;
    }
    x = 0;
    i = 0;
    j++;
  }

  return c;
}
