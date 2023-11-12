#include <stdio.h>

int main()
{
  int n = 100;
  int arr[n];

  // Inicializar o array
  for (int i = 0; i < n; i++)
  {
    arr[i] = i;
  }

// Dividir o loop em 4 chunks
#pragma omp distribute parallel for
  for (int i = 0; i < n; i++)
  {
    // Executar cada iteração do loop em uma thread diferente
    printf("arr[%d] = %d\n", i, arr[i]);
  }

  return 0;
}
