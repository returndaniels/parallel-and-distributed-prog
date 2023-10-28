#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>

void sieveOfEratosthenes(int n)
{
  int *prime = (int *)malloc((n + 1) * sizeof(int));
  int i, p, count = 0;

#pragma omp parallel for
  for (i = 0; i <= n; i++)
  {
    prime[i] = 1;
  }

  prime[0] = 0;
  prime[1] = 0;

  for (p = 2; p * p <= n; p++)
  {
    if (prime[p] == 1)
    {
#pragma omp parallel for
      for (i = p * p; i <= n; i += p)
      {
        prime[i] = 0;
      }
    }
  }

#pragma omp parallel for reduction(+ : count)
  for (i = 2; i <= n; i++)
  {
    if (prime[i] == 1)
    {
      count++;
    }
  }

  printf("O total de números primos entre 2 e %d é: %d\n", n, count);

  free(prime);
}

int main(int argc, char *argv[])
{
  int n = -1;

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-nt") == 0)
    {
      if (i < argc)
      {
        int num_threads;
        num_threads = atoi(argv[i + 1]);
        omp_set_num_threads(num_threads);
      }
    }
    else if (strcmp(argv[i], "-N") == 0)
      if (i < argc)
        n = atoi(argv[i + 1]);
  }

  if (n == -1)
  {
    printf("Digite o valor de N: ");
    scanf("%d", &n);
  }
  else
    printf("O valor de N é: %d\n", n);

  clock_t start, end;
  double cpu_time_used;

  start = clock();
  sieveOfEratosthenes(n);
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  return 0;
}
