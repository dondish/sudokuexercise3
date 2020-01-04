OBJS = main.o mainaux.o game.o parser.o solver.o
CC = gcc
EXEC = sudoku
CFLAGS = -g -ansi -Wall -Wextra -Werror -pedantic-errors

all: $(EXEC)

parser_test: parser_test.c parser.h parser.o
	$(CC) $(CFLAGS) parser_test.c parser.o -o parser_test

game_test: game_test.c game.h game.o
	$(CC) $(CFLAGS) game_test.c game.o -o game_test


solver_test: solver_test.c solver.h solver.o game.h game.o
	$(CC) $(CFLAGS) solver_test.c solver.o game.o -o solver_test

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@

main.o: main.c mainaux.h game.h parser.h solver.h
	$(CC) $(CFLAGS) -c $*.c

mainaux.o: mainaux.c mainaux.h game.h parser.h solver.h
	$(CC) $(CFLAGS) -c $*.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c $*.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c $*.c

solver.o: solver.c solver.h game.h game.o
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(EXEC)
