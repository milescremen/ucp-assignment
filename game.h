


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
#define EMPTY_TILE ' ' 

/* Typedefs */
typedef struct {
   char value;
   int row;
   int col;
} Tile;

typedef struct {
   int gameNum;
   LinkedList* moves;
} GameLog;

typedef struct {
   int turn;
   char player;
   int xLocation;
   int yLocation;
} MoveLog;

/* Forward Declarations */
void game(int width, int height, int matching, LinkedList* logs);
Tile** setup(int width, int height, int matching);
void display(Tile** board, int width, int height);
void userInput(Tile** board, int width, int height, int matching, LinkedList* logs);
int playerMove(Tile** board, int width, int height, int matching, char* player, char playerTile, int moveCount);

int checkWin(Tile** board, int width, int height, int matching, int row, int col, char playerTile);
int checkHorizontal(Tile** board, int width, int height, int matching, int row, int col, char playerTile);
int checkVertical(Tile** board, int width, int height, int matching, int row, int col, char playerTile);
int checkDiagonal(Tile** board, int width, int height, int matching, int row, int col, char playerTile);
int checkAntiDiagonal(Tile** board, int width, int height, int matching, int row, int col, char playerTile);
#endif
