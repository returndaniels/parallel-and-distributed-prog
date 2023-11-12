#include <stdio.h>
#include <omp.h>

int main()
{
  const int size = 100000;
  int array[size];

  // Inicializa o array
  for (int i = 0; i < size; ++i)
    array[i] = i;

// Uso da diretiva pragma omp for para paralelizar o loop
#pragma omp parallel for
  for (int i = 0; i < size; ++i)
    array[i] = array[i] * 2;

  // Imprime alguns valores do array
  for (int i = 0; i < 10; ++i)
    printf("array[%d] = %d\n", i, array[i]);

  return 0;
}