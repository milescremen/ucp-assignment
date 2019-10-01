#include "game.h"
/* CAlls the other methods to run a game */
void game(int width, int height, int matching)
{
    Tile** board;
    board = setup(width, height, matching);
    display(board, width, height);
}

/* Creates the board and initializes the tiles 
    The board is constructed of a 2d array*/
Tile** setup(int width, int height, int matching)
{
    int i, j; 
    Tile** board;
    Tile defaultTile;

    defaultTile.value = " ";
    defaultTile.row = -1;
    defaultTile.col = -1;

    /* Create the outer 2d array that holds the rows */ 
    board = (Tile**)malloc((height) * sizeof(Tile*));
    for(i = 0; i < height; i++)
    {
        /* Create the inner arrays (rows) */
        board[i] = (Tile*)malloc((width) * sizeof(Tile));
    }

    /* Initialize the tiles with default tile structs */
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            board[i][j] = defaultTile;
        }
    } 
    return board;  
}

/* Prints out the Board */
void display(Tile** board, int width, int height)
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            printf("%s ", board[i][j].value);
        }
    }   
}

void userInput()
{

}






