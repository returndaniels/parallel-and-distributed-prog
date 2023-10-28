CC = gcc
CFLAGS = -O3
OMP_FLAGS = -fopenmp
TARGET_DIR = bin
OUTPUT_DIR = out

.PHONY: all clean

all: seq_primos omp_primos run_tests

seq_primos: sieve_of_eratosthenes.c | create_dir
	$(CC) $(CFLAGS) sieve_of_eratosthenes.c -o $(TARGET_DIR)/seq_primos

omp_primos: omp_sieve_of_eratosthenes.c | create_dir
	$(CC) $(OMP_FLAGS) $(CFLAGS) omp_sieve_of_eratosthenes.c -o $(TARGET_DIR)/omp_primos

create_dir:
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(OUTPUT_DIR)

run_tests: 
	@echo "Rodando testes com 1 thread..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/omp_primos -nt 1 >> $(OUTPUT_DIR)/n1.txt; done
	@echo "Rodando testes com 8 thread..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/omp_primos -nt 8 >> $(OUTPUT_DIR)/n8.txt; done
	@echo "Rodando testes com 16 thread..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/omp_primos -nt 16 >> $(OUTPUT_DIR)/n16.txt; done
	@echo "Rodando testes com 32 thread..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/omp_primos -nt 32 >> $(OUTPUT_DIR)/n32.txt; done
	@echo "Rodando testes com 64 thread..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/omp_primos -nt 64 >> $(OUTPUT_DIR)/n64.txt; done

clean:
	rm -rf $(TARGET_DIR)/seq_primos $(TARGET_DIR)/omp_primos $(OUTPUT_DIR)/*.txt
