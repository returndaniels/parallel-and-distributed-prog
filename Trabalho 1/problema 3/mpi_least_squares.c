#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{

  double *x, *y;
  double mySUMx, mySUMy, mySUMxy, mySUMxx, SUMx, SUMy, SUMxy,
      SUMxx, SUMres, res, slope, y_intercept, y_estimate;
  int i, j, n, myid, numprocs, naverage, nremain, mypoints, ishift;
  MPI_Status istatus;
  FILE *infile;

  infile = fopen("xydata", "r");
  if (infile == NULL)
    printf("erro ao abrir o arquivo\n");

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // Passo 1: O Processo 0 lê os dados e transmite o valor de n
  if (myid == 0)
  {
    printf("Número de processos usados: %d\n", numprocs);
    printf("-------------------------------------\n");
    printf("As coordenadas x nos processos de trabalho:\n");
    fscanf(infile, "%d", &n);
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
      fscanf(infile, "%lf %lf", &x[i], &y[i]);
    for (i = 1; i < numprocs; i++)
      MPI_Send(&n, 1, MPI_INT, i, 10, MPI_COMM_WORLD);
  }
  else
  {
    MPI_Recv(&n, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &istatus);
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));
  }

  /* ----------------------------------------------------------
   * Passo 2: O Processo 0 envia subconjuntos de x e y
   * ---------------------------------------------------------- */
  naverage = n / numprocs;
  nremain = n % numprocs;
  if (myid == 0)
  {
    for (i = 1; i < numprocs; i++)
    {
      ishift = i * naverage;
      mypoints = (i < numprocs - 1) ? naverage : naverage + nremain;
      MPI_Send(&ishift, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      MPI_Send(&mypoints, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
      MPI_Send(&x[ishift], mypoints, MPI_DOUBLE, i, 3, MPI_COMM_WORLD);
      MPI_Send(&y[ishift], mypoints, MPI_DOUBLE, i, 4, MPI_COMM_WORLD);
    }
  }
  else
  {
    MPI_Recv(&ishift, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &istatus);
    MPI_Recv(&mypoints, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &istatus);
    MPI_Recv(&x[ishift], mypoints, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD,
             &istatus);
    MPI_Recv(&y[ishift], mypoints, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD,
             &istatus);
    printf("id %d: ", myid);
    for (i = 0; i < n; i++)
      printf("%4.2lf ", x[i]);
    printf("\n");
  }

  /* ----------------------------------------------------------
   * Passo 3: Cada processo calcula a sua soma parcial
   * ---------------------------------------------------------- */
  mySUMx = 0;
  mySUMy = 0;
  mySUMxy = 0;
  mySUMxx = 0;
  if (myid == 0)
  {
    ishift = 0;
    mypoints = naverage;
  }
  for (j = 0; j < mypoints; j++)
  {
    mySUMx = mySUMx + x[ishift + j];
    mySUMy = mySUMy + y[ishift + j];
    mySUMxy = mySUMxy + x[ishift + j] * y[ishift + j];
    mySUMxx = mySUMxx + x[ishift + j] * x[ishift + j];
  }

  /* ----------------------------------------------------------
   * Passo 4: Todos os processos realizam uma operação de redução
   * para obter as somas globais
   * ---------------------------------------------------------- */
  MPI_Reduce(&mySUMx, &SUMx, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&mySUMy, &SUMy, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&mySUMxy, &SUMxy, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&mySUMxx, &SUMxx, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  /* ----------------------------------------------------------
   * Passo 5: O Processo 0 calcula a linha de regressão linear
   * ---------------------------------------------------------- */
  if (myid == 0)
  {
    slope = (SUMx * SUMy - n * SUMxy) / (SUMx * SUMx - n * SUMxx);
    y_intercept = (SUMy - slope * SUMx) / n;

    printf("\n");
    printf("A equação linear que melhor se ajusta aos dados fornecidos:\n");
    printf("       y = %6.2lfx + %6.2lf\n", slope, y_intercept);
    printf("--------------------------------------------------\n");
    printf("   Original (x,y)     Estimativa de y     Residual\n");
    printf("--------------------------------------------------\n");

    SUMres = 0;
    for (i = 0; i < n; i++)
    {
      y_estimate = slope * x[i] + y_intercept;
      res = y[i] - y_estimate;
      SUMres = SUMres + res * res;
      printf("   (%6.2lf %6.2lf)      %6.2lf       %6.2lf\n",
             x[i], y[i], y_estimate, res);
    }
    printf("--------------------------------------------------\n");
    printf("Soma dos resíduos = %6.2lf\n", SUMres);
  }

  /* ----------------------------------------------------------	*/
  MPI_Finalize();

  free(x);
  free(y);

  return 0;
}
