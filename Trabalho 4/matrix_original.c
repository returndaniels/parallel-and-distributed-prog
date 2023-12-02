#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

void matrix_multiply(int **a, int **b, int **x)
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        x[i][j] += a[i][k] * b[k][j];
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
  int **o;

  a = (int **)malloc(N * sizeof(int *));
  b = (int **)malloc(N * sizeof(int *));
  o = (int **)malloc(N * sizeof(int *));
  for (int i = 0; i < N; i++)
  {
    a[i] = (int *)malloc(N * sizeof(int));
    b[i] = (int *)malloc(N * sizeof(int));
    o[i] = (int *)malloc(N * sizeof(int));
  }

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);

  for (long int i = 0; i < N * N; i++)
  {
    o[i / N][i % N] = 0;
  }

  /**
   * TESTE DA FUNÇÃO ORIGINAL
   */
  // start_time = clock();
  matrix_multiply(a, b, o);
  // end_time = clock();
  // total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  // printf("Original) Tempo de execucao: %.10f segundos.\n", total_time);

  /**
   * SAIDAS
   */
  // printf("Matriz o:\n");
  // for (int i = 0; i < N; i++)
  // {
  //   for (int j = 0; j < N; j++)
  //     printf("%2d ", o[i][j]);
  //   printf("\n");
  // }
  // printf("\n");

  return 0;
}