#Makefile Variables
CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -std=c89 -g
#CFLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Werror -fverbose-asm -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors -std=gnu11 -ggdb
OBJ = main.o userinterface.o game.o linkedlist.o filemanager.o
EXEC = tictactoe

ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

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