#include "game.h"
#include <time.h>
/* CAlls the other methods to run a game */
void game(int width, int height, int matching, LinkedList* logs)
{
    Tile** board;
    board = setup(width, height, matching);
    userInput(board, width, height, logs);
}

/* Creates the board and initializes the tiles 
    The board is constructed of a 2d array*/
Tile** setup(int width, int height, int matching)
{
    int x,y; 
    Tile** board;
    Tile defaultTile;

    defaultTile.value = EMPTY_TILE;
    defaultTile.row = -1;
    defaultTile.col = -1;

    /* Create the outer 2d array that holds the rows */ 
    board = (Tile**)malloc((height) * sizeof(Tile*));
    for(y = 0; y < height; y++)
    {
        /* Create the inner arrays (rows) */
        board[y] = (Tile*)malloc((width) * sizeof(Tile));
    }
    /* 
            Board will look like this 
            Where X = Column and Y = Row 
                
              X  0    1    2    3
            Y  ____________________
            0 | 0,0| 1,0| 2,0| 3,0|
            1 | 1,0| 1,1| 1,2| 1,3|
            2 | 2,0| 2,1| 2,2| 2,3|
            3 | 3,0| 3,1| 3,2| 3,3|
    */
    /* Initialize the tiles with default tile structs */
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            board[x][y] = defaultTile;
            board[x][y].col = x;
            board[x][y].row = y;
        }
    } 
    return board;  
}

/* Prints out the Board */
void display(Tile** board, int width, int height)
{
    int i, j, k;

    /* Prints numbers above board */
    for(i = 0; i <= width; i++)
    {
        printf("   %d", i);
    }
    printf("\n ");
    /* Prints first border of board */
    for(i = 0; i < width; i++)
    {
        printf("=====");
    }
    /* Prints out the rows of the board */
    for(i = 0; i < height; i++)
    {
        printf("\n%d|", i);
        for(j = 0; j < width; j++)
        {
            /*printf(" %d,%d ", board[i][j].row, board[i][j].col);*/
            printf(" %s |", board[i][j].value); 
        }
        printf("\n ");
        /* Prints out the line seperators */
        for(k = 0; k < width; k++)
        {
            printf("-----");
        }
    }   
    printf("\n ");
    /* Prints out the base border of the game */
    for(i = 0; i < width; i++)
    {
        printf("=====");
    }
}

void userInput(Tile** board, int width, int height, LinkedList* logs)
{
    int moveCount; /* Current number of moves */
    int maxMoves; /* Maximum of moves until game is finished */
    char* playerOne;
    char* playerTwo;
    char* playerOneTile;    /* String containing the players tile */
    char* playerTwoTile;

    /* Possibly store these as constants??? */
    playerOne = "Player One";
    playerTwo = "Player Two";
    playerOneTile = "X";
    playerTwoTile = "O";

    /* Possible moves, allows calculation of when the game should end*/
    /* PROBLEM: Game just ends and doesn't print out who wins */
    maxMoves = width * height;
    moveCount = 0;
    while(moveCount < maxMoves)
    {
        playerMove(board, width, height, playerOne, playerOneTile);
        moveCount++;
        playerMove(board, width, height, playerTwo, playerTwoTile);
        moveCount++;
    }
    
}

void playerMove(Tile** board, int width, int height, char* player, char* playerTile)
{
    int row;
    int col;
    int nRead;
    int inputted;
    inputted = FALSE;
    while(inputted == FALSE)
    {
        display(board, width, height);
        printf("\n%s, Please enter coords to place a %s\n", player, playerTile);
        nRead = scanf("%d,%d", &row, &col);
        if(nRead == 2)
        {
            /* Validates if the input value is within the board */
            if((row < height && row >= 0) && (col < width && col >= 0))
            {
                /* Checks if the tile is occupied */
                if(strcmp(board[col][row].value, EMPTY_TILE) == 0)
                {
                    board[col][row].value = playerTile;
                    inputted = TRUE; /* Ends the loop asking for input */
                }
                else
                {
                    printf("ERROR: Tile is already occupied, please try again\n");
                }
            }
            else
            {
                printf("ERROR: Coords not in range of board, please try again\n");
            }  
        }
        else
        {
            printf("ERROR: Invalid coords inputted, please try again\n");
        }
    }
}