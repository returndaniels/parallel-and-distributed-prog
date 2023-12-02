#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000

void matrix_multiply_02(int *a, int *b, int *c, int size)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
      int *pa = a + i * size;     // Ponteiro para a linha i da matriz a
      int *pb = b + j;            // Ponteiro para a coluna j da matriz b
      int *pc = c + i * size + j; // Ponteiro para x[i][j]

      *pc = 0; // Inicializa o valor de x[i][j]

      for (int k = 0; k < size; k++)
      {
        *pc += *pa * *pb; // Acumula o valor de x[i][j]
        pa++;
        pb += size; // Move para a próxima linha em b
      }
    }
}

void preencherMatrizAleatoria(int *matriz)
{
  srand(time(NULL));

  for (int i = 0; i < N * N; i++)
    matriz[i] = rand() % 100;
}

int main()
{

  clock_t start_time, end_time;
  double total_time;

  int *a = (int *)malloc(N * N * sizeof(int));
  int *b = (int *)malloc(N * N * sizeof(int));
  int *c = (int *)malloc(N * N * sizeof(int));

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);

  srand(time(NULL));

  /**
   * TESTE DA FUNÇÃO 2
   */

  // start_time = clock();
  matrix_multiply_02(a, b, c, N);
  // end_time = clock();
  // total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  // printf("D) Tempo de execucao: %.10f segundos.\n", total_time);

  /**
   * SAIDAS
   */
  // printf("Matriz resultante c:\n");
  // for (int i = 0; i < N * N; i++)
  // {
  //   printf("%d ", c[i]);
  //   if ((i + 1) % N == 0)
  //     printf("\n");
  // }
  // printf("\n");

  return 0;
}