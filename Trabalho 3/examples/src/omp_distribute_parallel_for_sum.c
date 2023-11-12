#include <stdio.h>

int main()
{
  long int n = 1000000;
  long int arr[n];

  // Inicializar o array
  for (long int i = 0; i < n; i++)
  {
    arr[i] = i;
  }

  // Calcular a soma dos elementos do array
  long int sum = 0;

// Dividir o loop em 100 chunks
#pragma omp distribute parallel for reduction(+ : sum)
  for (long int i = 0; i < n; i++)
  {
    // Executar cada iteração do loop em uma thread diferente
    sum += arr[i];
  }

  // Imprimir a soma
  printf("A soma é %ld\n", sum);

  return 0;
}
