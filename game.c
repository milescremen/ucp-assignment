#include "game.h"
#include <time.h>


/* CAlls the other methods to run a game */
void game(int width, int height, int matching, LinkedList* logs)
{
    Tile** board;
    board = setup(width, height, matching);
    userInput(board, width, height, matching, logs);
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
    board = (Tile**)malloc((width) * sizeof(Tile*));
    for(y = 0; y < width; y++)
    {
        /* Create the inner arrays (rows) */
        board[y] = (Tile*)malloc((height) * sizeof(Tile));
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
    for(x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
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
    for(i = 0; i < width; i++)
    {
        printf("   %d", i);
    }
    printf("\n ");
    /* Prints first border of board */
    for(i = 0; i < width; i++)
    {
        printf("====");
    }
    /* Prints out the rows of the board */
    for(i = 0; i < height; i++)
    {
        printf("\n%d|", i);
        for(j = 0; j < width; j++)
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
        if(i != height - 1)
        {
            for(k = 0; k < width; k++)
            {
                printf("----");
            }
        }
    }   
    /* Prints out the base border of the game */
    for(i = 0; i < width; i++)
    {
        printf("====");
    }
}

void userInput(Tile** board, int width, int height, int matching, LinkedList* logs)
{
    GameLog gameLog;
    MoveLog* move; 
    int moveCount; /* Current number of moves */
    int maxMoves; /* Maximum of moves until game is finished */
    char* playerOne;
    char* playerTwo;
    char playerOneTile;    /* String containing the players tile */
    char playerTwoTile;

    /* Creating the linked list for the games log */
    gameLog.moves = createLinkedList();    

    /* Possibly store these as constants??? */
    playerOne = "Player One";
    playerTwo = "Player Two";
    playerOneTile = 'X';
    playerTwoTile = 'O';

    /* Possible moves, allows calculation of when the game should end*/
    /* PROBLEM: Game just ends and doesn't print out who wins */
    maxMoves = width * height;
    moveCount = 0;
    while(moveCount < maxMoves || winner != FALSE)
    {
        moveCount++;
        move = playerMove(board, width, height, matching, playerOne, playerOneTile, moveCount);
        insertFirst(move, gameLog.moves);
        
        if(winner != TRUE)
        {
            moveCount++;
            move = playerMove(board, width, height, matching, playerTwo, playerTwoTile, moveCount);
            insertFirst(move, gameLog.moves);
        }
    }
}

int playerMove(Tile** board, int width, int height, int matching, char* player, char playerTile, int moveCount)
{
    MoveLog* move; /* Struct created to store the logs for moves */ 
    int row;
    int col;
    int nRead;
    int inputted;
    int winner;
    winner = FALSE;
    inputted = FALSE;
    while(inputted == FALSE)
    {
        display(board, width, height);
        printf("\n%s, Please enter coords to place a %c\n", player, playerTile);
        nRead = scanf("%d,%d", &col, &row);
        if(nRead == 2)
        {
            /* Validates if the input value is within the board */
            if((row < height && row >= 0) && (col < width && col >= 0))
            {
                /* Checks if the tile is occupied */
                if(board[col][row].value == EMPTY_TILE)
                {
                    board[col][row].value = playerTile;
                    inputted = TRUE; /* Ends the loop asking for input */

                    /* Stores the information for the current move in the new MoveLog struct */
                    move = (MoveLog*)malloc(sizeof(MoveLog));
                    move -> player = playerTile;
                    move -> xLocation = col;
                    move -> yLocation = row;
                    move -> turn = moveCount;
                     
                    winner = checkWin(board, width, height, matching, row, col, playerTile);
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
    return move;
}

int checkWin(Tile** board, int width, int height, int matching, int row, int col, char playerTile)
{
    int winner;
    if(checkHorizontal(board, width, height, matching, row, col, playerTile) == TRUE
        || checkVertical(board, width, height, matching, row, col, playerTile) == TRUE
        || checkDiagonal(board, width, height, matching, row, col, playerTile) == TRUE
        || checkAntiDiagonal(board, width, height, matching, row, col, playerTile) == TRUE)
    {
        winner = TRUE;
    }
    else
    {
        winner = FALSE;
    }
    return winner;
}

int checkHorizontal(Tile** board, int width, int height, int matching, int row, int col, char playerTile)
{
    int count; /* Keeps count of the amount of adjacent playerTiles */
    int leftColIndex;
    int rightColIndex;
    int done;
    char winner;

    count = 1; 
    leftColIndex = 0;
    rightColIndex = 0;
    done = FALSE; 
    winner = FALSE;

    /* Iterates to the left */
    leftColIndex = col - 1; /* Starts the column index to the left of the inputted tile */
    rightColIndex = col + 1; /* Starts the column index to the right of the inputted tile */
    /* Then while their is matching tiles, it will iterate to the left and right
        incrementing the count */
    while(done == FALSE && leftColIndex > -1 && rightColIndex < width) /* Checks if the tile is matching to the players tile */
    {
        if(count >= matching) /* Ends loop early */
        {
            done = TRUE;
            winner = TRUE;
        }
        else if(board[leftColIndex][row].value == playerTile) /* Iterates left */
        {
            leftColIndex--; /* Moves index to the left */
            count++;
        }
        else if(board[rightColIndex][row].value == playerTile) /* Iterates right */
        {
            rightColIndex++;
            count++;
        }
        else
        {
            done = TRUE;
        }
    }

    printf("Horizontal COUNT: %d\n", count); 
    return winner;
}


int checkVertical(Tile** board, int width, int height, int matching, int row, int col, char playerTile)
{
    int count; /* Keeps count of the amount of adjacent playerTiles */
    int done;
    int upRowIndex;
    int downRowIndex;
    int winner;

    count = 1; 
    done = FALSE; 
    winner = FALSE; 

    /* Iterates upwards */
    upRowIndex = row - 1; /* Starts the row index to above the inputted tile */
    downRowIndex = row + 1; /* Starts the row index to below of the inputted tile */

    /* Then while their is matching tiles, it will iterate to the left
        incrementing the count */
    while(done == FALSE && upRowIndex > -1 && downRowIndex < height) /* Checks if the tile is matching to the players tile */
    {
        if(count >= matching)
        {
            done = TRUE;
            winner = TRUE;
        }
        else if(board[col][upRowIndex].value == playerTile)
        {
            upRowIndex--; /* Moves index to the left */
            count++;
        }
        else if(board[col][downRowIndex].value == playerTile)
        {
            downRowIndex++;
            count++;
        }
        else
        {
            done = TRUE;
        }
    }

    printf("Vertical COUNT: %d\n", count); 
    return winner;
}

int checkDiagonal(Tile** board, int width, int height, int matching, int row, int col, char playerTile)
{
    /* Keeps count of the amount of adjacent playerTiles */
    int count;
    char winner;
    /* Iterates up and to the left */
    int upColIndex;
    int upRowIndex;
    /* Iterates down and to the right */
    int downColIndex; 
    int downRowIndex;
    int done;

    count = 1; 
    done = FALSE; 
    winner = FALSE;
    /* Starts the column index to the left of the inputted tile */
    upRowIndex = row - 1;
    upColIndex = col - 1;
    /* Starts the column index to the right of the inputted tile */
    downRowIndex = row + 1;  
    downColIndex = col + 1;

    /* Then while their is matching tiles, it will iterate up
        incrementing the count */
    while(done == FALSE && upRowIndex > -1 && upColIndex > -1 && downRowIndex < height && downColIndex < width) /* Checks if the tile is matching to the players tile */
    {
        if(count >= matching)
        {
            done = TRUE;
            winner = TRUE;
        }
        else if(board[upColIndex][upRowIndex].value == playerTile)
        {
            upRowIndex--; /* Moves Up 1 diagonally */
            upColIndex--;
            count++;
        }
        else if(board[downColIndex][downRowIndex].value == playerTile)
        {
            downRowIndex++;
            downColIndex++;
            count++;
        }
        else
        {
            done = TRUE;
        }
    }

    printf("Diagonal COUNT: %d\n", count); 
    return winner;
}


int checkAntiDiagonal(Tile** board, int width, int height, int matching, int row, int col, char playerTile)
{
    int count; /* Keeps count of the amount of adjacent playerTiles */
    int done;
    int winner;
    /* Iterates up and to the right */
    int upColIndex;
    int upRowIndex;
    /* Iterates down and to the left */
    int downColIndex;
    int downRowIndex;
    count = 1; 
    done = FALSE; 
    winner = FALSE;

    upRowIndex = row - 1; /* Starts the column index to the left of the inputted tile */
    upColIndex = col + 1;
    downRowIndex = row + 1; /* Starts the column index to the right of the inputted tile */
    downColIndex = col - 1;
    /* Then while their is matching tiles, it will iterate up
        incrementing the count */
    while(done == FALSE && upRowIndex > -1 && upColIndex < width && downRowIndex < height && downColIndex > -1) /* Checks if the tile is matching to the players tile */
    {
        if(count >= matching)
        {
            done = TRUE;
            winner = TRUE;
        } 
        else if(board[upColIndex][upRowIndex].value == playerTile)
        {
            upRowIndex--; /* Moves Up 1 diagonally */
            upColIndex++;
            count++;
        }
        else if(board[downColIndex][downRowIndex].value == playerTile)
        {
            downRowIndex++;
            downColIndex--;
            count++;
        }
        else
        {
            done = TRUE;
        }
    }
    
    printf("Anti Diagonal COUNT: %d\n", count); 
    return winner;
}



