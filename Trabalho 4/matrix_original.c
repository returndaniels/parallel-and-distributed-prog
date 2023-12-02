#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n;

void matrix_multiply(int **a, int **b, int **c)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        c[i][j] += a[i][k] * b[k][j];
}

void preencherMatrizAleatoria(int **matriz)
{
  int i, j;
  srand(time(NULL));

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      matriz[i][j] = rand() % 100;
    }
  }
}

int main(int argc, char const *argv[])
{
  n = atoi(argv[1]);

  clock_t start_time, end_time;
  double total_time;

  int **a;
  int **b;
  int **c;

  a = (int **)malloc(n * sizeof(int *));
  b = (int **)malloc(n * sizeof(int *));
  c = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    a[i] = (int *)malloc(n * sizeof(int));
    b[i] = (int *)malloc(n * sizeof(int));
    c[i] = (int *)malloc(n * sizeof(int));
  }

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);

  for (int i = 0; i < n * n; i++)
  {
    c[i / n][i % n] = 0;
  }

  start_time = clock();
  matrix_multiply(a, b, c);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("%.10f\n", total_time);

  return 0;
}