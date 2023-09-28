#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const int array_size = 100;
  int *data = NULL;
  int local_sum = 0;
  int global_sum = 0;

  if (rank == 0)
  {
    // Initialize the data array on the root process
    data = (int *)malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; ++i)
    {
      data[i] = i + 1; // Initialize data with values 1 to array_size
    }
  }

  // Distribute the data among all processes
  MPI_Bcast(data, array_size, MPI_INT, 0, MPI_COMM_WORLD);

  // Calculate the local sum of elements for each process
  int local_elements = array_size / size;
  int local_start = rank * local_elements;
  int local_end = local_start + local_elements;
  for (int i = local_start; i < local_end; ++i)
  {
    local_sum += data[i];
  }

  // Reduce the local sums to obtain the global sum
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Print the result on the root process
  if (rank == 0)
  {
    printf("Global sum: %d\n", global_sum);
    free(data);
  }

  MPI_Finalize();

  return 0;
}
