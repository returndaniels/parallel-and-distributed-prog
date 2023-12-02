#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000

void transpose(int *b, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = i + 1; j < size; j++)
    {
      int temp = *(b + i * size + j);
      *(b + i * size + j) = *(b + j * size + i);
      *(b + j * size + i) = temp;
    }
}

void matrix_multiply_03(int *a, int *b, int *x, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
      int *pa = a + i * size;     // Ponteiro para a linha i da matriz a
      int *pb = b + j * size;     // Ponteiro para a coluna j da matriz b transposta
      int *pc = x + i * size + j; // Ponteiro para c[i][j]

      *pc = 0; // Inicializa o valor de c[i][j]

      for (int k = 0; k < size; k++)
      {
        *pc += *pa * *pb; // Acumula o valor de c[i][j]
        pa++;
        pb++;
      }
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

  int *d = (int *)malloc(N * N * sizeof(int));
  int *g = (int *)malloc(N * N * sizeof(int));
  int *h = (int *)malloc(N * N * sizeof(int));

  a = (int **)malloc(N * sizeof(int *));
  b = (int **)malloc(N * sizeof(int *));
  for (int i = 0; i < N; i++)
  {
    a[i] = (int *)malloc(N * sizeof(int));
    b[i] = (int *)malloc(N * sizeof(int));
  }

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);

  for (long int i = 0; i < N * N; i++)
  {
    d[i] = a[i / N][i % N];
    g[i] = b[i / N][i % N];
  }

  /**
   * TESTE DA FUNÇÃO 3
   */
  transpose((int *)g, N);

  // start_time = clock();
  matrix_multiply_03(d, g, h, N);
  // end_time = clock();
  // total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  // printf("H) Tempo de execucao: %.10f segundos.\n", total_time);

  /**
   * SAIDAS
   */
  // printf("Matriz resultante h:\n");
  // for (int i = 0; i < N * N; i++)
  // {
  //   printf("%d ", h[i]);
  //   if ((i + 1) % N == 0)
  //     printf("\n");
  // }
  // printf("\n");

  return 0;
}