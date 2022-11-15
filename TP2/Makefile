CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means
CFLAGS = "-O2" "-funroll-loops" "-ffast-math" "-fopenmp"
.DEFAULT_GOAL = k_means
THREADS = 2
CP_CLUSTERS = 4

k_means:
	$(CC) $(CFLAGS) $(SRC)k_means_with_1st_opt.c -o $(BIN)$(EXEC)

clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS)
runpar:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) $(THREADS)

