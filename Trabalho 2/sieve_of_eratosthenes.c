#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sieveOfEratosthenes(int n)
{
  int *prime = (int *)malloc((n + 1) * sizeof(int));
  int i, p, count = 0;

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

  printf("O total de números primos entre 2 e %d é: %d\n", n, count);

  free(prime);
}

int main(int argc, char *argv[])
{
  int n;

  if (argc < 2)
  {
    printf("Digite o valor de N: ");
    scanf("%d", &n);
  }
  else
  {
    n = atoi(argv[1]);
    printf("O valor de N é: %d\n", n);
  }

  clock_t start, end;
  double cpu_time_used;

  start = clock();
  sieveOfEratosthenes(n);
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  return 0;
}
