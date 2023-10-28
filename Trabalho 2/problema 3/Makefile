CC = gcc
CFLAGS = -O3
LM_FLAGS = -lm
OMP_FLAGS = -fopenmp
TARGET_DIR = bin
OUTPUT_DIR = out
PROGRAM = omp_simulation

.PHONY: all clean testes

all: omp_simulation

omp_simulation: omp_metal_plate_heat_simulation.c | create_dir
	$(CC) $(LM_FLAGS) $(OMP_FLAGS) $(CFLAGS) omp_metal_plate_heat_simulation.c -o $(TARGET_DIR)/$(PROGRAM)

create_dir:
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(OUTPUT_DIR)

testes: 
	rm -rf $(OUTPUT_DIR)/*.txt
	@echo "Rodando testes com 1 thread..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/$(PROGRAM) -nt 1 >> $(OUTPUT_DIR)/n1.txt; done
	@echo "Rodando testes com 8 threads..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/$(PROGRAM) -nt 8 >> $(OUTPUT_DIR)/n8.txt; done
	@echo "Rodando testes com 16 threads..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/$(PROGRAM) -nt 16 >> $(OUTPUT_DIR)/n16.txt; done
	@echo "Rodando testes com 32 threads..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/$(PROGRAM) -nt 32 >> $(OUTPUT_DIR)/n32.txt; done
	@echo "Rodando testes com 64 threads..."
	@for i in $$(seq 1 5); do $(TARGET_DIR)/$(PROGRAM) -nt 64 >> $(OUTPUT_DIR)/n64.txt; done

clean:
	rm -rf $(TARGET_DIR)/seq_primos $(TARGET_DIR)/omp_primos $(OUTPUT_DIR)/*.txt
