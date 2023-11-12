CC = gcc
CFLAGS = -Wall -fopenmp

SRC_DIR = src
BIN_DIR = bin

EXAMPLE01 = omp_parallel
EXAMPLE02 = omp_parallel_for
EXAMPLE03 = omp_distribute_parallel_for_array
EXAMPLE04 = omp_distribute_parallel_for_sum
EXAMPLE05 = omp_image_filter

.PHONY: all clean 

all: example_01 example_02 example_03 example_04 example_05

example_01: $(SRC_DIR)/$(EXAMPLE01).c | create_dir
	$(CC) $(CFLAGS) $(SRC_DIR)/$(EXAMPLE01).c -o $(BIN_DIR)/$(EXAMPLE01)

example_02: $(SRC_DIR)/$(EXAMPLE02).c | create_dir
	$(CC) $(CFLAGS) $(SRC_DIR)/$(EXAMPLE02).c -o $(BIN_DIR)/$(EXAMPLE02)

example_03: $(SRC_DIR)/$(EXAMPLE03).c | create_dir
	$(CC) $(CFLAGS) $(SRC_DIR)/$(EXAMPLE03).c -o $(BIN_DIR)/$(EXAMPLE03)

example_04: $(SRC_DIR)/$(EXAMPLE04).c | create_dir
	$(CC) $(CFLAGS) $(SRC_DIR)/$(EXAMPLE04).c -o $(BIN_DIR)/$(EXAMPLE04)

example_05: $(SRC_DIR)/$(EXAMPLE05).c | create_dir
	$(CC) $(CFLAGS) $(SRC_DIR)/$(EXAMPLE05).c -o $(BIN_DIR)/$(EXAMPLE05)

create_dir:
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

