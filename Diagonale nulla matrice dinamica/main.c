#include <stdio.h>
#include <stdlib.h>

void diagonal_zero(int** mat, int dim);
void print_matrix(int**mat, int dim);

int main ()
{
  int R;
  scanf("%d", &R);

  int **mat;
  mat =(int**) malloc(sizeof(int*)*R);
  for(int i = 0; i < R; i++)
  {
    mat[i] = (int *)malloc(sizeof(int)*R);
  }
  
  for(int i = 0; i < R; i++)
  {
    for(int j = 0; j < R; j++)
    { 
      scanf("%d", &mat[i][j]);
    }
   }

  diagonal_zero(mat,R);
  print_matrix(mat,R);

}

void diagonal_zero(int** mat, int dim)
{
  int i = 0, j = 0, k = dim - 1;
  while(i < dim)
  {
    mat[i][j] = 0;
    mat[i][k] = 0;
    i++;
    j++;
    k--;
  }
}

void print_matrix(int **mat, int dim)
{
  for(int i = 0; i < dim; i++)
  {
    for(int j = 0; j < dim; j++)
    {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}
