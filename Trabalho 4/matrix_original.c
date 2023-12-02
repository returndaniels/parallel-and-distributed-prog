#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n;

void matrix_multiply(int **a, int **b, int **x)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        x[i][j] += a[i][k] * b[k][j];
}

void preencherMatrizAleatoria(int **matriz)
{
  long long int i, j;
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
  int **o;

  a = (int **)malloc(n * sizeof(int *));
  b = (int **)malloc(n * sizeof(int *));
  o = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    a[i] = (int *)malloc(n * sizeof(int));
    b[i] = (int *)malloc(n * sizeof(int));
    o[i] = (int *)malloc(n * sizeof(int));
  }

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);

  for (long int i = 0; i < n * n; i++)
  {
    o[i / n][i % n] = 0;
  }

  start_time = clock();
  matrix_multiply(a, b, o);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("%.10f\n", total_time);

  return 0;
}