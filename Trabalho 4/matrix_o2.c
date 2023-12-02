#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000

void matrix_multiply_02(int *a, int *b, int *x, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
      int *pa = a + i * size;     // Ponteiro para a linha i da matriz a
      int *pb = b + j;            // Ponteiro para a coluna j da matriz b
      int *pc = x + i * size + j; // Ponteiro para x[i][j]

      *pc = 0; // Inicializa o valor de x[i][j]

      for (int k = 0; k < size; k++)
      {
        *pc += *pa * *pb; // Acumula o valor de x[i][j]
        pa++;
        pb += size; // Move para a próxima linha em b
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
  int **o;

  int *d = (int *)malloc(N * N * sizeof(int));
  int *e = (int *)malloc(N * N * sizeof(int));
  int *f = (int *)malloc(N * N * sizeof(int));

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
    e[i] = b[i / N][i % N];
  }

  /**
   * TESTE DA FUNÇÃO 2
   */

  // start_time = clock();
  matrix_multiply_02(d, e, f, N);
  // end_time = clock();
  // total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  // printf("D) Tempo de execucao: %.10f segundos.\n", total_time);

  /**
   * SAIDAS
   */
  // printf("Matriz resultante f:\n");
  // for (int i = 0; i < N * N; i++)
  // {
  //   printf("%d ", f[i]);
  //   if ((i + 1) % N == 0)
  //     printf("\n");
  // }
  // printf("\n");

  return 0;
}