#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000

void matrix_multiply_01(int a[N][N], int b[N][N], int x[N][N])
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
      int temp = 0;
      for (int k = 0; k < N; k++)
        temp += a[i][k] * b[k][j];
      x[i][j] = temp;
    }
}

void preencherMatrizAleatoria(int **matriz)
{
  long long int i, j;
  srand(time(NULL));

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      matriz[i][j] = rand() % 100;
    }
  }
}

int main()
{

  clock_t start_time, end_time;
  double total_time;

  int **a;
  int **b;
  int **c;

  a = (int **)malloc(N * sizeof(int *));
  b = (int **)malloc(N * sizeof(int *));
  c = (int **)malloc(N * sizeof(int *));
  for (int i = 0; i < N; i++)
  {
    a[i] = (int *)malloc(N * sizeof(int));
    b[i] = (int *)malloc(N * sizeof(int));
    c[i] = (int *)malloc(N * sizeof(int));
  }

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);

  /**
   * TESTE DA FUNÇÃO 1
   */
  // start_time = clock();
  matrix_multiply_01(a, b, c);
  // end_time = clock();
  // total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  // printf("C) Tempo de execucao: %.10f segundos.\n", total_time);

  /**
   * SAIDAS
   */
  // printf("Matriz c:\n");
  // for (int i = 0; i < N; i++)
  // {
  //   for (int j = 0; j < N; j++)
  //     printf("%2d ", c[i][j]);
  //   printf("\n");
  // }
  // printf("\n");

  return 0;
}