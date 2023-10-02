#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEFAULT_N 10
#define DEFAULT_FILENAME "coordenadas.txt"
#define MAX_ABS_ERROR 1.0

int main()
{
  srand(time(NULL));

  int N;
  char filename[100];

  printf("Digite o valor de N (ou deixe em branco para o padrão %d): ", DEFAULT_N);
  char input[100];

  if (fgets(input, sizeof(input), stdin) != NULL)
  {
    if (input[0] == '\n')
      N = DEFAULT_N;
    else
      sscanf(input, "%d", &N);
  }
  else
    N = DEFAULT_N;

  printf("Digite o nome do arquivo (ou deixe em branco para o padrão '%s'): ", DEFAULT_FILENAME);
  if (fgets(input, sizeof(input), stdin) != NULL)
  {
    if (input[0] == '\n')
      strcpy(filename, DEFAULT_FILENAME);
    else
      sscanf(input, "%99s", filename);
  }
  else
    strcpy(filename, DEFAULT_FILENAME);

  FILE *file = fopen(filename, "w");

  if (file == NULL)
  {
    perror("Erro ao abrir o arquivo");
    return 1;
  }
  fprintf(file, "%d\n", N);

  for (int i = 0; i < N; i++)
  {
    double X = i;
    double Y = 2 * X + ((rand() % (int)(2 * MAX_ABS_ERROR * 10 + 1) - MAX_ABS_ERROR * 10) / 10.0); // Equação Y = 2X + erro aleatório
    fprintf(file, "%.2lf %.2lf\n", X, Y);                                                          // Escreve no arquivo
  }
  fclose(file);

  printf("Arquivo gerado com sucesso: %s\n", filename);

  return 0;
}
