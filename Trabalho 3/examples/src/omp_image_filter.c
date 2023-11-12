#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  // Inicializar a imagem
  int width = 100;
  int height = 100;
  int image[width][height];
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      image[i][j] = rand() % 256;
    }
  }

  // Definir o limiar
  int threshold = 128;

// Filtrar a imagem
#pragma omp distribute parallel for
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      // Se o pixel for maior que o limiar, setá-lo para branco
      if (image[i][j] > threshold)
      {
        image[i][j] = 255;
      }
      // Senão, setá-lo para preto
      else
      {
        image[i][j] = 0;
      }
    }
  }

  // Imprimir a imagem filtrada
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      printf("%d ", image[i][j]);
    }
    printf("\n");
  }

  return 0;
}