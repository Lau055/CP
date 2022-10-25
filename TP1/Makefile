CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means
CFLAGS = -O3
.DEFAULT_GOAL = k_means
k_means:
	$(CC) $(CFLAGS) $(SRC)k_means_with_1st_opt.c -o $(BIN)$(EXEC)

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)