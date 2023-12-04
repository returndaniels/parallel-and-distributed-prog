#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

int n;

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

void block_multiply(int *a, int *b, int *x, int size, int block_size)
{
  for(int bi = 0; bi < size; bi += block_size)
    for (int bj = 0; bj < size; bj += block_size)
      for (int bk = 0; bk < size; bk += block_size)
        {
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
}

void preencherMatrizAleatoria(int *matriz)
{
  srand(time(NULL));

  for (int i = 0; i < n * n; i++)
    matriz[i] = rand() % 100;
}


int main(int argc, char const *argv[])
{
  n = atoi(argv[1]);

  clock_t start_time, end_time;
  double total_time;

  int *a = (int *) malloc(n * n * sizeof(int));
  int *b = (int *) malloc(n * n * sizeof(int));
  int *c = (int *) malloc(n * n * sizeof(int));

  int block_size = 2;

  preencherMatrizAleatoria(a);
  preencherMatrizAleatoria(b);
  transpose((int *)b, n);

  start_time = clock();
  block_multiply(a, b, c, n, block_size);

  end_time = clock();
  total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("%.10f\n", total_time);

  return 0;
}