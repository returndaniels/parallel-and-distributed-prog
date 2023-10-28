#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10 // Tamanho da grade
#define M 1000 // Número de iterações
#define SOR_FACTOR 1.5 // Fator de relaxamento

void initializePlate(double plate[N][N]) {
  for (int i = 0; i < N; i++) 
    for (int j = 0; j < N; j++) {
      if (i == 0 || j == 0 || i == N - 1 || j == N - 1) 
        plate[i][j] = 100.0; // Temperatura fixa nas bordas
      else 
        plate[i][j] = 0.0; // Temperatura inicial em outros lugares
    }
}

// Imprime a placa
void printPlate(double plate[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("%.2f\t", plate[i][j]);
    printf("\n");
  }
  printf("\n");
}

// Simulação de Gauss-Seidel SOR
void simulate(double plate[N][N]) {
  double oldPlate[N][N];
  double error = 1.0; // Erro inicial
  int iteration = 0;

  while (iteration < M && error > 0.0001) {
      error = 0.0;
      for (int i = 1; i < N - 1; i++) 
        for (int j = 1; j < N - 1; j++) {
            oldPlate[i][j] = plate[i][j];
            plate[i][j] = (1 - SOR_FACTOR) * plate[i][j] + SOR_FACTOR * 0.25 * (plate[i-1][j] + plate[i][j-1] + plate[i][j+1] + plate[i+1][j]);
            double currentError = fabs(plate[i][j] - oldPlate[i][j]);
            if (currentError > error) 
              error = currentError;
        }
      iteration++;
  }
}

int main() {
    double plate[N][N];

    initializePlate(plate);
    printf("Placa inicial:\n");
    printPlate(plate);

    simulate(plate);
    printf("Placa final:\n");
    printPlate(plate);

    return 0;
}
