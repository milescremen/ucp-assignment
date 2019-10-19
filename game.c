#include "game.h"


/* FOR SOME REASON IF I ENTER 0,02 it stills works as 0,2 */

/* Calls the other methods to run a game */
void game(Settings* settings, LinkedList* logs)
{
    Tile** board;
    int moveCount; /* Current number of moves */
    int maxMoves; /* Maximum of moves until game is finished */
    char* playerOne;
    char* playerTwo;
    char playerOneTile;    /* String containing the players tile */
    char playerTwoTile;
    int winner;

    /* Static variable keeps the number of games played for logging purposes */ 
    static int gameCount;
    gameCount++;

    /* Sets up the board */
    board = setupBoard(settings);
    winner = FALSE;

    /* Possibly store these as constants??? */
    playerOne = "Player One";
    playerTwo = "Player Two";
    playerOneTile = 'X';
    playerTwoTile = 'O';

    /* Possible moves, allows calculation of when the game should end*/

    maxMoves = (settings -> width) * (settings -> height);
    moveCount = 0;
    while(moveCount < maxMoves && winner == FALSE) /* DOUBLE CHECK THE LAST MOVE */
    {
        moveCount++;
        winner = playerMove(board, settings, playerOne, playerOneTile, moveCount, gameCount, logs);
        /* Checks that player one hasn't won the game */

        printf("move %d\n", moveCount);
        if(moveCount < maxMoves && winner == FALSE)
        {
            moveCount++;
            winner = playerMove(board, settings, playerTwo, playerTwoTile, moveCount, gameCount, logs);
        }
    }

    /* The game has ended after the while loop finishes, so now to check who won */
    if(winner == TRUE)
    {
        /* Player one always goes first, so we mod to find the winner */
        if(moveCount % maxMoves != 0)
        {
            displayBoard(board, settings);
            printf("\nPlayer One is the winner!!!\n");
        }
        else
        {
            displayBoard(board, settings);
            printf("\nPlayer Two is the winner!!!\n");
        }
    }
    else
    {
        displayBoard(board, settings);
        printf("\nIts a draw :(\n");
    }
    freeBoard(board, settings); 
}

/* Creates the board and initializes the tiles 
    The board is constructed of a 2d array*/
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

Tile** setupBoard(Settings* settings)
{
    int x,y;                                            
    Tile** board;
    Tile defaultTile;

    defaultTile.value = EMPTY_TILE;
    defaultTile.row = -1;
    defaultTile.col = -1;

    /* Create the outer 2d array that holds the rows */ 
    board = (Tile**)malloc((settings -> width) * sizeof(Tile*));
    for(y = 0; y < settings -> width; y++)
    {
        /* Create the inner arrays (rows) */
        board[y] = (Tile*)malloc((settings -> height) * sizeof(Tile));
    }
    /* Initialize the tiles with default tile structs */
    for(x = 0; x < settings -> width; x++)
    {
        for(y = 0; y < settings -> height; y++)
        {
            board[x][y] = defaultTile;
            board[x][y].col = x;
            board[x][y].row = y;
        }
    } 
    return board;  
}

void freeBoard(Tile** board, Settings* settings)
{
    int y;
    for(y = 0; y < settings -> width; y++)
    {
        /* Free the inner arrays (rows) */
        free(board[y]);
    }
    free(board);
}

/* Prints out the Board */
void displayBoard(Tile** board, Settings* settings)
{
    int i, j, k;

    /* Prints numbers above board */
    for(i = 0; i < settings -> width; i++)
    {
        printf("   %d", i);
    }
    printf("\n ");
    /* Prints first border of board */
    for(i = 0; i < settings -> width; i++)
    {
        printf("====");
    }
    /* Prints out the rows of the board */
    for(i = 0; i < settings -> height; i++)
    {
        printf("\n%d|", i);
        for(j = 0; j < settings -> width; j++)
        {
            /*printf(" %d,%d ", board[i][j].row, board[i][j].col);*/
            printf(" %c |", board[j][i].value); 
            /* have to print backwards because my arrays are stored like this 
            COLUMN ARRAY 
            R R R           
            O O O
            W W W
            1 2 3*/
        }
        printf("\n ");
        /* Prints out the line seperators 
            but checks that it isn't the last line */
        if(i != (settings -> height - 1))
        {
            for(k = 0; k < settings -> width; k++)
            {
                printf("----");
            }
        }
    }   
    /* Prints out the base border of the game */
    for(i = 0; i < settings -> width; i++)
    {
        printf("====");
    }
}

int playerMove(Tile** board, Settings* settings, char* player, char playerTile, int moveCount, int gameCount, LinkedList* logs)
{
    MoveLog* move; /* Struct created to store the logs for moves */ 
    int row;
    int col;
    int nRead;
    int inputted;
    int winner;
    winner = FALSE;
    inputted = FALSE;

    printf("PLayer tile T: %c\n", playerTile);
    while(inputted == FALSE)
    {
        displayBoard(board, settings);
        printf("\n%s, Please enter coords to place a %c\n", player, playerTile);
        nRead = scanf("%d,%d", &col, &row);
        if(nRead == 2)
        {
            /* Validates if the input value is within the board */
            if((row < settings -> height && row >= 0) && (col < settings -> width && col >= 0))
            {
                /* Checks if the tile is occupied */
                if(board[col][row].value == EMPTY_TILE)
                {
                    board[col][row].value = playerTile;
                    inputted = TRUE; /* Ends the loop asking for input */

                    /* Stores the information for the current move in the new MoveLog struct */
                    move = (MoveLog*)malloc(sizeof(MoveLog));
                    move -> game = gameCount;
                    move -> player = playerTile;
                    move -> xLocation = col;
                    move -> yLocation = row;
                    move -> turn = moveCount;
                    insertLast(move, logs);
                    winner = checkWin(board, settings, row, col, playerTile);
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
    return winner;
}

int checkWin(Tile** board, Settings* settings, int row, int col, char playerTile)
{
    int winner;
    if(checkHorizontal(board, settings, row, col, playerTile) == TRUE
        || checkVertical(board, settings, row, col, playerTile) == TRUE
        || checkDiagonal(board, settings, row, col, playerTile) == TRUE
        || checkAntiDiagonal(board, settings, row, col, playerTile) == TRUE)
    {
        winner = TRUE;
    }
    else
    {
        winner = FALSE;
    }
    return winner;
}

int checkHorizontal(Tile** board, Settings* settings, int row, int col, char playerTile)
{
    int count; /* Keeps count of the amount of adjacent playerTiles */
    int leftColIndex;
    int rightColIndex;
    int isEqual;
    int winner;

    count = 1; 
    leftColIndex = 0;
    rightColIndex = 0;
    isEqual = TRUE; 
    winner = FALSE;

    /* Iterates to the left */
    leftColIndex = col - 1; /* Starts the column index to the left of the inputted tile */
    rightColIndex = col + 1; /* Starts the column index to the right of the inputted tile */
    /* Then while their is matching tiles, it will iterate to the left and right
        incrementing the count */

    while(leftColIndex > -1 && isEqual == TRUE)
    {
        if(board[leftColIndex][row].value == playerTile) /* Iterates left */
        {
            leftColIndex--; /* Moves index to the left */
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }

    if(count >= settings -> matching) 
    {
        winner = TRUE;
    }
    else
    {
        isEqual = TRUE;
    }
    /* Additional boolean check winner == FALSE included because 
        if we find a winner in previous loop, we don't need to check the otherwise */
    while(rightColIndex < settings -> width && isEqual == TRUE) 
    {
        if(board[rightColIndex][row].value == playerTile) /* Iterates right */
        {
            rightColIndex++;
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }
 
    if(count >= settings -> matching) 
    {
        winner = TRUE;
    }
    return winner;
}


int checkVertical(Tile** board, Settings* settings, int row, int col, char playerTile)
{
    int count; /* Keeps count of the amount of adjacent playerTiles */
    int upRowIndex;
    int downRowIndex;
    int isEqual;
    int winner;

    count = 1; 
    isEqual = TRUE; 
    winner = FALSE; 

    /* Iterates upwards */
    upRowIndex = row - 1; /* Starts the row index to above the inputted tile */
    downRowIndex = row + 1; /* Starts the row index to below of the inputted tile */

    while(upRowIndex > -1 && isEqual == TRUE)
    {
        if(board[col][upRowIndex].value == playerTile)
        {
            upRowIndex--; /* Moves index to the left */
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }

    if(count >= settings -> matching) 
    {
        winner = TRUE;
    }
    else
    {
        isEqual = TRUE;
    }
    while(downRowIndex < settings -> height && isEqual == TRUE)
    {
        if(board[col][downRowIndex].value == playerTile)
        {
            downRowIndex++;
            count++;
        }
        else
        {
            isEqual = FALSE;
        }   
    }

    if(count >= settings -> matching) 
    {
        winner = TRUE;
    }
    /* Then while their is matching tiles, it will iterate to the left
        incrementing the count */
    return winner;
}

int checkDiagonal(Tile** board, Settings* settings, int row, int col, char playerTile)
{
    /* Keeps count of the amount of adjacent playerTiles */
    int count;
    int winner;
    /* Iterates up and to the left */
    int upColIndex;
    int upRowIndex;
    /* Iterates down and to the right */
    int downColIndex; 
    int downRowIndex;
    int isEqual;
    count = 1; 
    isEqual = TRUE; 
    winner = FALSE;
    /* Starts the column index to the left of the inputted tile */
    upRowIndex = row - 1;
    upColIndex = col - 1;
    /* Starts the column index to the right of the inputted tile */
    downRowIndex = row + 1;  
    downColIndex = col + 1;

    while(upRowIndex > -1 && upColIndex > -1 && isEqual == TRUE)
    {
        if(board[upColIndex][upRowIndex].value == playerTile)
        {
            upRowIndex--; /* Moves Up 1 diagonally */
            upColIndex--;
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }

    if(count >= settings -> matching) 
    {
        winner = TRUE;
    }
    else
    {
        isEqual = TRUE;
    }

    isEqual = TRUE;
    while(downRowIndex < settings -> height && downColIndex < settings -> width 
            && isEqual == TRUE)
    {
        if(board[downColIndex][downRowIndex].value == playerTile)
        {
            downRowIndex++;
            downColIndex++;
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }

    if(count >= settings -> matching)
    {
        winner = TRUE;
    }
    printf("D COUNT: %d\n", count); 
    return winner;
}

int checkAntiDiagonal(Tile** board, Settings* settings, int row, int col, char playerTile)
{
    int count; /* Keeps count of the amount of adjacent playerTiles */
    int isEqual;
    int winner;
    /* Iterates up and to the right */
    int upColIndex;
    int upRowIndex;
    /* Iterates down and to the left */
    int downColIndex;
    int downRowIndex;
    count = 1; 
    isEqual = TRUE;
    winner = FALSE;

    upRowIndex = row - 1; /* Starts the column index to the left of the inputted tile */
    upColIndex = col + 1;
    downRowIndex = row + 1; /* Starts the column index to the right of the inputted tile */
    downColIndex = col - 1;
    /* Then while their is matching tiles, it will iterate up
        incrementing the count */

    while(upRowIndex > -1 && upColIndex < settings -> width && isEqual == TRUE)
    {
        if(board[upColIndex][upRowIndex].value == playerTile)
        {
            upRowIndex--; /* Moves Up 1 diagonally */
            upColIndex++;
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }

    if(count >= settings -> matching) 
    {
        winner = TRUE;
    }
    else
    {
        isEqual = TRUE;
    }

    while(downRowIndex < settings ->height && downColIndex > -1 &&
            isEqual == TRUE)
    {
        if(board[downColIndex][downRowIndex].value == playerTile)
        {
            downRowIndex++;
            downColIndex--;
            count++;
        }
        else
        {
            isEqual = FALSE;
        }
    }

    if(count >= settings -> matching)
    {
        winner = TRUE;
    } 

        printf("AD COUNT: %d\n", count); 
    return winner;
}


