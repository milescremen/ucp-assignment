
#ifndef GAME_H
#define GAME_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include <time.h>
#include "filemanager.h"

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
   int game;
   int turn;
   char player;
   int xLocation;
   int yLocation;
} MoveLog;

/* Forward Declarations */
void game(Settings* settings, LinkedList* logs);
Tile** setupBoard(Settings* settings);
void freeBoard(Tile** board, Settings* settings);
void displayBoard(Tile** board, Settings* settings);
void userInput(Tile** board, Settings* settings, LinkedList* logs);
int playerMove(Tile** board, Settings* settings, char* player, char playerTile, int moveCount, int gameCount, LinkedList* logs);

int checkWin(Tile** board, Settings* settings, int row, int col, char playerTile);
int checkHorizontal(Tile** board, Settings* settings, int row, int col, char playerTile);
int checkVertical(Tile** board, Settings* settings, int row, int col, char playerTile);
int checkDiagonal(Tile** board, Settings* settings, int row, int col, char playerTile);
int checkAntiDiagonal(Tile** board, Settings* settings, int row, int col, char playerTile);
#endif
