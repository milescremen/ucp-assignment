


#ifndef GAME_H
#define GAME_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

/* Defines */
#define FALSE 0
#define TRUE !FALSE
#define EMPTY_TILE " "

/* Typedefs */
typedef struct {
   char* value;
   int row;
   int col;
} Tile;

/* Forward Declarations */
void game(int width, int height, int matching, LinkedList* logs);
Tile** setup(int width, int height, int matching);
void display(Tile** board, int width, int height);
void userInput(Tile** board, int width, int height, LinkedList* logs);
void playerMove(Tile** board, int width, int height, char* player, char* playerTile);

#endif
