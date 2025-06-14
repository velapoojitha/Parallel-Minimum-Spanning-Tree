# Compiler and flags
CC = gcc
CFLAGS = -Wall
OMPFLAGS = -fopenmp

# Executable names
PARALLEL_EXEC = parallel_mst
SEQUENTIAL_EXEC = sequential_mst
GENERATOR_EXEC = generator

# Source files
PARALLEL_SRC = parallel_mst.c
SEQUENTIAL_SRC = sequential_mst.c
GENERATOR_SRC = pmst_generatelarge_inputs.c

# Default target
all: $(PARALLEL_EXEC) $(SEQUENTIAL_EXEC) $(GENERATOR_EXEC)

$(PARALLEL_EXEC): $(PARALLEL_SRC)
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $<

$(SEQUENTIAL_EXEC): $(SEQUENTIAL_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(GENERATOR_EXEC): $(GENERATOR_SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Clean compiled files
clean:
	rm -f $(PARALLEL_EXEC) $(SEQUENTIAL_EXEC) $(GENERATOR_EXEC) *.o *.txt
