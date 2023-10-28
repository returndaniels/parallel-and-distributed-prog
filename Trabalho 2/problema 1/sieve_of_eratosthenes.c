#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 300000000

void sieveOfEratosthenes(long long int n)
{
  int *prime = (int *)malloc((n + 1) * sizeof(int));
  long long int i, p, count = 0;

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
      for (i = p * p; i <= n; i += p)
      {
        prime[i] = 0;
      }
    }
  }

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

  if (argc >= 2)
    n = atoll(argv[1]);
  printf("O valor de N é: %lld\n", n);

  clock_t start, end;
  double cpu_time_used;

  start = clock();
  sieveOfEratosthenes(n);
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  return 0;
}
