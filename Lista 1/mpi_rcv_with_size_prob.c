#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int rank, size, source, tag;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Status status;
  int message_size;
  // Suponha que você deseja receber uma mensagem com a etiqueta 1 do processo 0
  if (rank == 0)
  {
    int data_to_send[] = {1, 2, 3, 4, 5}; // Seu dado de exemplo
    int send_count = 5;                   // Número de elementos no array
    source = 0;                           // Processo de origem
    tag = 1;                              // Etiqueta da mensagem
    MPI_Send(data_to_send, send_count, MPI_INT, 1, tag, MPI_COMM_WORLD);
  }
  else if (rank == 1)
  {
    // Use MPI_Probe para verificar se há uma mensagem vindo do processo 0
    MPI_Probe(0, 1, MPI_COMM_WORLD, &status);
    // Use MPI_Get_count para obter o tamanho da mensagem
    MPI_Get_count(&status, MPI_INT, &message_size);
    // Aloque um vetor com o tamanho exato da mensagem
    int *received_data = (int *)malloc(sizeof(int) * message_size);
    // Receba a mensagem no vetor alocado
    MPI_Recv(received_data, message_size, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // Imprima os dados recebidos
    printf("Processo %d recebeu uma mensagem com tamanho %d:\n", rank, message_size);
    for (int i = 0; i < message_size; i++)
      printf("%d ", received_data[i]);
    printf("\n");

    // Libere a memória alocada
    free(received_data);
  }
  MPI_Finalize();
  return 0;
}
