#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int rank, num_procs;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  int valor = -1;                                 // Valor inicial da mensagem (processo 0 definirá o valor real)
  int dest = (rank + 1) % num_procs;              // Próximo processo no anel
  int fonte = (rank + num_procs - 1) % num_procs; // Processo anterior no anel

  if (rank == 0)
  {
    // Processo 0 define o valor inicial da mensagem
    valor = 10; // Defina o valor desejado
    printf("Processo %d enviou a mensagem inicial: %d\n", rank, valor);
  }

  while (1)
  {
    // Todos os processos passam a mensagem adiante no anel
    MPI_Send(&valor, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    MPI_Recv(&valor, 1, MPI_INT, fonte, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Processo %d recebeu a mensagem: %d\n", rank, valor);

    // Se o valor atingir 0, o processo encerra
    if (valor == 0)
    {
      printf("Processo %d terminou.\n", rank);
      break;
    }

    // Decrementa o valor
    valor--;
  }
  MPI_Finalize();
  return 0;
}
