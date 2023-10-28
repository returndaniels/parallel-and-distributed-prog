#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

#define N 3000000000

void sieveOfEratosthenes(long long int n)
{
  int *prime = (int *)malloc((n + 1) * sizeof(int));
  long long int i, p, count = 0;

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

  printf("O total de números primos entre 2 e %lld é: %lld\n", n, count);

  free(prime);
}

int main(int argc, char *argv[])
{
  long long int n = N;

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
        n = atoll(argv[i + 1]);
  }

  printf("O valor de N é: %lld\n", n);

  double start, end, cpu_time_used;

  start = omp_get_wtime();
  sieveOfEratosthenes(n);
  end = omp_get_wtime();

  cpu_time_used = end - start;
  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  return 0;
}
