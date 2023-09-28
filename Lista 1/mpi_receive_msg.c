#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAX_MESSAGE_LENGTH 100

int main(int argc, char *argv[])
{
  int rank, num_procs;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  char mensagem[MAX_MESSAGE_LENGTH] = "Mensagem de exemplo";

  /* Versão 1: Recepção pelo processo com índice (num_procs - 1) */
  if (rank == num_procs - 1)
  {
    char received_message[MAX_MESSAGE_LENGTH];
    MPI_Recv(
        received_message,
        MAX_MESSAGE_LENGTH,
        MPI_CHAR,
        MPI_ANY_SOURCE,
        MPI_ANY_TAG,
        MPI_COMM_WORLD,
        MPI_STATUS_IGNORE);
    printf("Processo %d recebeu a mensagem: %s\n", rank, received_message);
  }

  /* Versão 2: Recepção por todos os processos */
  char received_message[MAX_MESSAGE_LENGTH];
  MPI_Recv(
      received_message,
      MAX_MESSAGE_LENGTH,
      MPI_CHAR,
      MPI_ANY_SOURCE,
      MPI_ANY_TAG,
      MPI_COMM_WORLD,
      MPI_STATUS_IGNORE);
  printf("Processo %d recebeu a mensagem: %s\n", rank, received_message);

  /* Versão 3: Recepção em ordem sequencial */
  MPI_Recv(
      received_message,
      MAX_MESSAGE_LENGTH,
      MPI_CHAR,
      rank - 1,
      1,
      MPI_COMM_WORLD,
      MPI_STATUS_IGNORE);

  if (rank != num_procs - 1)
  {
    MPI_Send(
        received_message,
        strlen(received_message) + 1,
        MPI_CHAR,
        rank + 1,
        1,
        MPI_COMM_WORLD);
  }

  printf("Processo %d recebeu a mensagem: %s\n", rank, received_message);

  MPI_Finalize();
  return 0;
}
