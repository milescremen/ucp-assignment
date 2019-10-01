#Makefile Variables
CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror
OBJ = tictactoe.o userInterface.o game.o
EXEC = tictactoe

#Executable creation 
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

tictactoe.o : tictactoe.c tictactoe.h
	$(CC) tictactoe.c -c $(CFLAGS)

userInterface.o : userInterface.c userInterface.h
	$(CC) userInterface.c -c $(CFLAGS)

game.o : game.c game.h
	$(CC) game.c -c $(CFLAGS)

clean :
	rm -f $(OBJ) $(EXEC)