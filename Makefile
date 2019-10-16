#Makefile Variables
CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -std=c89 -g
OBJ = main.o userinterface.o game.o linkedlist.o filemanager.o
EXEC = tictactoe

#Executable creation 
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -g

main.o : main.c
	$(CC) main.c -c $(CFLAGS)

userinterface.o : userinterface.c userinterface.h
	$(CC) userinterface.c -c $(CFLAGS)

game.o : game.c game.h
	$(CC) game.c -c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) linkedlist.c -c $(CFLAGS)

filemanager.o : filemanager.c filemanager.h
	$(CC) filemanager.c -c $(CFLAGS)

clean :
	rm -f $(OBJ) $(EXEC)