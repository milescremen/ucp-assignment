#Makefile Variables
CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror
OBJ = tictactoe.o
EXEC = tictactoe

#Executable creation 
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

tictactoe.o : tictactoe.c tictactoe.h
	$(CC) tictactoe.c -c $(CFLAGS)

clean :
	rm -f $(OBJ) $(EXEC)