#include <stdio.h>
#include <stdlib.h>

void multiply_matrices(int **A,int **B,int **C,int n,int m,int s);

int main()
{
  int N, M, S;
  scanf("%d", &N);
  scanf("%d", &M);
  scanf("%d", &S);
  
  int** mat1;
  mat1 =(int**)malloc(sizeof(int*)*N);
  for(int i = 0; i < N; i++)
  {
    mat1[i] =(int*)malloc(sizeof(int)*M);
  } 

  int** mat2;
  mat2 = (int**)malloc(sizeof(int*)*M);
  for(int i = 0; i < M; i++)
  {
    mat2[i] = (int*)malloc(sizeof(int)*S);
  }

  for(int i = 0; i < N; i++)
  { 
    for(int j = 0; j < M; j++)
    {
     scanf("%d", &mat1[i][j]);
    }
  }

  for(int i = 0; i < M; i++)
  { 
    for(int j = 0; j < S; j++)
    {
     scanf("%d", &mat2[i][j]);
    }
  }

  int** mat3;
  mat3 = (int**)malloc(sizeof(int*)*N);
  for(int i = 0; i < N; i++)
  {
    mat3[i] =(int*)malloc(sizeof(int)*S);
  }

  multiply_matrices(mat1,mat2,mat3,N,M,S);
  
  for(int i = 0; i < N; i++)
  { 
    for(int j = 0; j < S; j++)
    {
     printf("%d ", mat3[i][j]);
    }
    printf("\n");
  }
  free(mat1);
  free(mat2);
  free(mat3);
}

void multiply_matrices(int **A,int **B,int **C,int n,int m,int s)
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < s; j++)
    { 
      C[i][j] = 0;
      for(int k = 0; k < m; k++)
      {
        C[i][j] = C[i][j] + A[i][k]*B[k][j];
      }
    }
  }
}

