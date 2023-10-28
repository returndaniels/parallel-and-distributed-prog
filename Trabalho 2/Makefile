CC = gcc
CFLAGS = -O3
OMP_FLAGS = -fopenmp
TARGET_DIR = bin

.PHONY: all clean

all: seq_primos omp_primos

seq_primos: sieve_of_eratosthenes.c | create_dir
	$(CC) $(CFLAGS) sieve_of_eratosthenes.c -o $(TARGET_DIR)/seq_primos

omp_primos: omp_sieve_of_eratosthenes.c | create_dir
	$(CC) $(OMP_FLAGS) $(CFLAGS) omp_sieve_of_eratosthenes.c -o $(TARGET_DIR)/omp_primos

create_dir:
	@mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TARGET_DIR)/seq_primos $(TARGET_DIR)/omp_primos
