#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void matrix_multiply(int a[N][N], int b[N][N], int x[N][N])
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        x[i][j] += a[i][k] * b[k][j];
}

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

void block_multiply(int *a, int *b, int *x, int size, int block_size)
{
  for (int bi = 0; bi < size; bi += block_size)
    for (int bj = 0; bj < size; bj += block_size)
      for (int bk = 0; bk < size; bk += block_size)
        for (int i = bi; i < bi + block_size; i++)
          for (int j = bj; j < bj + block_size; j++)
          {
            int *pa = a + i * size + bk;
            int *pb = b + bk * size + j;
            int *pc = x + i * size + j;

            for (int k = 0; k < block_size; k++)
            {
              *pc += *pa * *pb;
              pa++;
              pb += size;
            }
          }
}

int main()
{

  clock_t start_time, end_time;
  double total_time;
  int a[N][N] = {
      {7, 3, 2, 1, 4, 6, 9, 2, 8, 2},
      {1, 1, 9, 1, 7, 9, 1, 8, 7, 1},
      {5, 9, 2, 8, 0, 7, 5, 9, 9, 7},
      {0, 2, 4, 0, 4, 4, 5, 1, 1, 5},
      {2, 9, 5, 3, 8, 2, 1, 3, 7, 3},
      {2, 4, 4, 1, 3, 9, 9, 3, 3, 5},
      {0, 0, 5, 9, 0, 7, 5, 2, 5, 3},
      {5, 9, 2, 0, 5, 9, 5, 8, 9, 1},
      {2, 5, 1, 0, 6, 3, 5, 1, 5, 5},
      {2, 1, 0, 0, 7, 9, 6, 7, 9, 0}};
  int b[N][N] = {
      {2, 4, 4, 6, 5, 7, 6, 1, 4, 8},
      {6, 6, 5, 0, 5, 6, 6, 1, 3, 9},
      {2, 2, 9, 5, 4, 2, 7, 9, 1, 6},
      {1, 1, 3, 7, 8, 6, 7, 8, 7, 2},
      {2, 9, 2, 7, 4, 7, 4, 8, 0, 5},
      {8, 3, 0, 0, 6, 3, 5, 5, 5, 7},
      {0, 6, 3, 5, 7, 5, 4, 1, 2, 7},
      {6, 0, 7, 3, 9, 6, 6, 3, 3, 7},
      {7, 3, 9, 3, 5, 8, 1, 7, 3, 9},
      {5, 7, 4, 6, 3, 0, 0, 0, 5, 6}};

  int c[N][N];
  int o[N][N];

  int *d = (int *)malloc(N * N * sizeof(int));
  int *e = (int *)malloc(N * N * sizeof(int));
  int *f = (int *)malloc(N * N * sizeof(int));

  int *g = (int *)malloc(N * N * sizeof(int));
  int *h = (int *)malloc(N * N * sizeof(int));

  int *l = (int *)malloc(N * N * sizeof(int));
  int block_size = 2;

  for (int i = 0; i < N * N; i++)
  {
    o[i / 10][i % 10] = 0;
    d[i] = a[i / 10][i % 10];
    e[i] = b[i / 10][i % 10];
    g[i] = b[i / 10][i % 10];
  }

  /**
   * TESTE DA FUNÇÃO ORIGINAL
   */
  start_time = clock();
  matrix_multiply(a, b, o);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("Original) Tempo de execucao: %.6f segundos.\n", total_time);

  /**
   * TESTE DA FUNÇÃO 1
   */
  start_time = clock();
  matrix_multiply_01(a, b, c);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("C) Tempo de execucao: %.6f segundos.\n", total_time);

  /**
   * TESTE DA FUNÇÃO 2
   */

  start_time = clock();
  matrix_multiply_02(d, e, f, N);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("D) Tempo de execucao: %.6f segundos.\n", total_time);

  /**
   * TESTE DA FUNÇÃO 3
   */
  transpose((int *)g, N);

  start_time = clock();
  matrix_multiply_03(d, g, h, N);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("H) Tempo de execucao: %.6f segundos.\n", total_time);

  /**
   * TESTE DA FUNÇÃO 4
   */
  transpose((int *)g, N);

  start_time = clock();
  block_multiply(d, g, l, N, block_size);
  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("L) Tempo de execucao: %.6f segundos.\n\n", total_time);

  /**
   * SAIDAS
   */
  printf("Matriz o:\n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      printf("%2d ", o[i][j]);
    printf("\n");
  }
  printf("\n");

  printf("Matriz c:\n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      printf("%2d ", c[i][j]);
    printf("\n");
  }
  printf("\n");

  printf("Matriz resultante f:\n");
  for (int i = 0; i < N * N; i++)
  {
    printf("%d ", f[i]);
    if ((i + 1) % N == 0)
      printf("\n");
  }
  printf("\n");

  printf("Matriz resultante h:\n");
  for (int i = 0; i < N * N; i++)
  {
    printf("%d ", h[i]);
    if ((i + 1) % N == 0)
      printf("\n");
  }
  printf("\n");

  printf("Matriz resultante l:\n");
  for (int i = 0; i < N * N; i++)
  {
    printf("%d ", l[i]);
    if ((i + 1) % N == 0)
      printf("\n");
  }
  printf("\n");

  return 0;
}