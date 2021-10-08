#include <stdio.h>

void multiplymatr(int matrix1[][2], int matrix2[][3], int matrix3[][3], int r1, int r2);

int main(){

  int n = 4;
  int s = 2;

  int a[4][2];
  int b[2][3];
  int c[4][3];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%d", &b[i][j]);
    }
  }

multiplymatr (a,b,c,n,s);

  for (int i = 0; i < 4; i++) {
    printf("\n");
    for (int j = 0; j < 3; j++) {
      printf(" %d", c[i][j]);
    }
  }
}

void multiplymatr(int matrix1[][2], int matrix2[][3], int matrix3[][3], int r1, int r2)
{
  for (int i = 0; i < r1; i++) {
    for (int j = 0; j < 3; j++) {
      matrix3[i][j] = 0;
      for (size_t k = 0; k < r2; k++) {
        matrix3[i][j] = matrix3[i][j] + matrix1[i][k]*matrix2[k][j];
      }
    }
  }
}
