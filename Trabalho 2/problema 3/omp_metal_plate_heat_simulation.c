#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1022             // Tamanho da placa
#define M 4098             // Número de iterações
#define SOR_FACTOR 1.3     // Fator de relaxamento
#define SOURCE_TEMP_X 800  // Posição x da fonte de calor
#define SOURCE_TEMP_Y 800  // Posição y da fonte de calor
#define SOURCE_TEMP 100.0  // Temperatura da fonte de calor
#define BOUNDARY_TEMP 20.0 // Temperatura das bordas

// Inicialização da placa
void initializePlate(double plate[N][N])
{
#pragma omp parallel for
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      plate[i][j] = BOUNDARY_TEMP;                   // Temperatura inicial
  plate[SOURCE_TEMP_X][SOURCE_TEMP_Y] = SOURCE_TEMP; // Configuração da fonte de calor
}

// Imprime a placa
void printPlate(double plate[N][N])
{
#pragma omp parallel for
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      printf("%.2f\t", plate[i][j]);
    printf("\n");
  }
  printf("\n");
}

// Simulação de Gauss-Seidel SOR
void simulate(double plate[N][N])
{
  double oldPlate[N][N];
  double error = 1.0; // Erro inicial
  int iteration = 0;

  while (iteration < M && error > 0.0001)
  {
    error = 0.1;
#pragma omp parallel for reduction(max : error) private(oldPlate)
    for (int i = 1; i < N - 1; i++)
      for (int j = 1; j < N - 1; j++)
      {
        double oldPlate = plate[i][j];

        // Excluir a fonte de calor dos cálculos
        if (i != SOURCE_TEMP_X || j != SOURCE_TEMP_Y)
          plate[i][j] = (1 - SOR_FACTOR) * plate[i][j] + SOR_FACTOR * 0.25 * (plate[i - 1][j] + plate[i][j - 1] + plate[i][j + 1] + plate[i + 1][j]);
        double currentError = fabs(plate[i][j] - oldPlate);
        if (currentError > error)
          error = currentError;
      }
    iteration++;
  }
}

int main()
{
  double plate[N][N];
  double start, end, cpu_time_used;

  initializePlate(plate);

  // Não imprimiremos a placa inicial novamente para evitar a repetição
  // printf("Placa inicial:\n");
  // printPlate(plate);

  start = omp_get_wtime();
  simulate(plate);
  end = omp_get_wtime();

  // Não imprimiremos a placa inicial novamente para evitar a repetição
  // printf("Placa final:\n");
  // printPlate(plate);

  cpu_time_used = end - start;
  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  return 0;
}
