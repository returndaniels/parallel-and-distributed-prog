#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	printf("1 %d %d", rank, size);
	MPI_Init(&argc, &argv);
	printf("2 %d %d", rank, size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int MAX_FLOAT = 10; // Tamanho máximo para o vetor
	float vetor[MAX_FLOAT];
	MPI_Status status;

	// Recebe a mensagem de qualquer processo com qualquer tag
	MPI_Recv(vetor, MAX_FLOAT, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	int sender_rank = status.MPI_SOURCE; // Processo que enviou a mensagem
	int tag = status.MPI_TAG;						 // Tag da mensagem
	int elements_received;
	MPI_Get_count(&status, MPI_FLOAT, &elements_received); // Número de elementos recebidos

	printf("Processo %d recebeu uma mensagem do processo %d com a etiqueta %d.\n", rank, sender_rank, tag);
	printf("Número total de elementos recebidos: %d\n", elements_received);

	MPI_Finalize();
	return 0;
}
