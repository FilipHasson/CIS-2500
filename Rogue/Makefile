CC = gcc
CFLAGS = -std=c99 -g
TFLAGS = -Wall -pedantic
LFLAGS = -lncurses -lm
INCLUDE = -Iinclude

SRCDIR = src
BINDIR = bin

SRC = $(SRCDIR)/*.c
OBJ = $(BINDIR)/*.o

bin/rogue: bin/main.o bin/parse.o bin/drawGame.o bin/debug.o bin/preGame.o bin/gameplay.o bin/inventory.o 
	$(CC) $(OBJ) $(LFLAGS) -o $(BINDIR)/rogue

bin/main.o: src/main.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/main.c -c -o $(BINDIR)/main.o

bin/parse.o: src/parse.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/parse.c -c -o $(BINDIR)/parse.o

bin/drawGame.o: src/drawGame.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/drawGame.c -c -o $(BINDIR)/drawGame.o

bin/debug.o: src/debug.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/debug.c -c -o $(BINDIR)/debug.o

bin/preGame.o: src/preGame.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/preGame.c -c -o $(BINDIR)/preGame.o

bin/gameplay.o: src/gameplay.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/gameplay.c -c -o $(BINDIR)/gameplay.o

bin/inventory.o: src/inventory.c
	$(CC) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(SRCDIR)/inventory.c -c -o $(BINDIR)/inventory.o

clean:
	rm -rf bin/*

all:
	gcc -Wall -pedantic -std=c99 ./src/main.c ./src/parse.c ./src/drawGame.c ./src/debug.c ./src/preGame.c ./src/gameplay.c ./src/inventory.c -Iinclude -lncurses -lm -o ./bin/runMe
