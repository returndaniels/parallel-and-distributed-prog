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