#include <stdio.h>
#include <stdlib.h>

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

int main()
{
  int n;
  printf("Digite o valor de N: ");
  scanf("%d", &n);
  sieveOfEratosthenes(n);
  return 0;
}
