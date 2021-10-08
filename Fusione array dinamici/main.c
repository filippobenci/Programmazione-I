#include <stdio.h>
#include <stdlib.h>

void fusion (int a1[],int*dim1, int a2[], int* dim2, int a3[]);
void array_sort (int a3[], int *dim3);
void swap (int *xp, int *yp);
int isSorted (int a3[], int* dim3);

int main()
{
  int d1,d2;
  scanf("%d", &d1);
  int *array1;
  array1 = malloc(d1*sizeof(int));

  for (size_t i = 0; i < d1; i++) {
    scanf("%d", &array1[i]);
  }
  scanf("%d", &d2);
  int *array2;
  array2 = malloc(d2*sizeof(int));

  for (size_t i = 0; i < d2; i++) {
    scanf("%d", &array2[i]);
  }
  int dim3 = d1 + d2;
  int *array3;
  array3 = malloc(dim3*sizeof(int));

  fusion(array1,&d1,array2,&d2,array3);
  array_sort(array3,&dim3);
  int s = isSorted(array3,&dim3);
  printf("Array A:\n");
  for (size_t i = 0; i < d1; i++) {
    printf("%d ", array1[i]);
  }
  printf("\n");
  printf("Array B:\n");
  for (size_t i = 0; i < d2; i++) {
    printf("%d ",array2[i]);
  }
  printf("\n");
  printf("Array risultato C\n");
  for (size_t i = 0; i < dim3; i++) {
    printf("%d ",array3[i]);
  }
  printf("\nOrdinato:  %d\n",s);
}

void fusion (int a1[],int*dim1, int a2[], int* dim2, int a3[])
{
  int k = *dim1;
  for (size_t i = 0; i < *dim1; i++) {
    a3[i] = a1[i];
  }
  for (size_t i = 0; i < *dim2 ; i++) {
    a3[k] = a2[i];
    k++;
  }
}

void array_sort(int a3[], int *dim3)
{
  int min_idx;
  for (size_t i = 0; i < *dim3-1; i++) {
    min_idx = i;
    for (size_t j = i+1; j < *dim3; j++) {
      if(a3[j] < a3[min_idx])
      {
        min_idx = j;
      }
    }
    swap(&a3[min_idx], &a3[i]);
  }
}

void swap (int* xp, int* yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int isSorted (int a3[], int *dim3)
{
  int flag = 0;
  for (size_t i = 0; i < *dim3-1; i++) {
    if(a3[i]<=a3[i+1])
    {
      flag = 1;
    }
    else return 0;
  }
  return flag;
}
