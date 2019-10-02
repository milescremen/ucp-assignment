#include "game.h"
#include <time.h>
/* CAlls the other methods to run a game */
void game(int width, int height, int matching)
{
    Tile** board;
    board = setup(width, height, matching);
    userInput(board, width, height);
}

/* Creates the board and initializes the tiles 
    The board is constructed of a 2d array*/
Tile** setup(int width, int height, int matching)
{
    int i, j; 
    Tile** board;
    Tile defaultTile;

    defaultTile.value = EMPTY_TILE;
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
            board[i][j].row = i;
            board[i][j].col = j;
        }
    } 
    return board;  
}

/* Prints out the Board */
void display(Tile** board, int width, int height)
{
    int i, j, k;

    /* Prints first border of board */
    for(i = 0; i < width; i++)
    {
        printf("=====");
    }
    /* Prints out the rows of the board */
    for(i = 0; i < height; i++)
    {
        printf("\n|");
        for(j = 0; j < width; j++)
        {
            /*printf("| %d,%d |", board[i][j].row, board[i][j].col);*/
            printf(" %s |", board[i][j].value);
        }
        printf("\n");
        /* Prints out the line seperators */
        for(k = 0; k < width; k++)
        {
            printf("-----");
        }
    }   
    printf("\n");
    /* Prints out the base border of the game */
    for(i = 0; i < width; i++)
    {
        printf("=====");
    }
}

void userInput(Tile** board, int width, int height)
{
    int player;
    int count;
    int maxMoves;

    /* Possible moves */
    maxMoves = width * height;
    /* srand(time(0));
    player = rand() % 2; */
    /* REMOOOOOOOOOOOOVE THIS HARDCODE */
    player = 1;
    count = 0;
    if(player == 1)
    {
        while(count < maxMoves)
        {
            playerOne(board, width, height);
            count++;
            playerTwo(board, width, height);
            count++;
        }
    } 
    else if(player == 2)
    {
        playerTwo(board, width, height);
        playerOne(board, width, height);
    }
}

void playerOne(Tile** board, int width, int height)
{
    int row;
    int col;
    int nRead;
    int inputted;
    inputted = FALSE;
    while(inputted == FALSE)
    {
        display(board, width, height);
        printf("\nPlayer One, Please enter coords to place an X\n");
        nRead = scanf("%d,%d", &row, &col);
        if(nRead == 2)
        {
            /* Validates if the input value is within the board */
            if((row < height && row >= 0) && (col < width && col >= 0))
            {
                /* Checks if the tile is occupied */
                if(strcmp(board[row][col].value, EMPTY_TILE) == 0)
                {
                    board[row][col].value = "X";
                    inputted = TRUE;
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

void playerTwo(Tile** board, int width, int height)
{
    int row;
    int col;
    int nRead;
    int inputted;
    inputted = FALSE;
    while(inputted == FALSE)
    {
        display(board, width, height);
        printf("\nPlayer Two, Please enter coords to place an O\n");
        nRead = scanf("%d,%d", &row, &col);
        if(nRead == 2)
        {
            /* Validates if the input value is within the board */
            if((row < height && row >= 0) && (col < width && col >= 0))
            {
                /* Checks if the tile is occupied */
                if(strcmp(board[row][col].value, EMPTY_TILE) == 0)
                {
                    board[row][col].value = "O";
                    /* Sets inputted to true, to end the loop */
                    inputted = TRUE;
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