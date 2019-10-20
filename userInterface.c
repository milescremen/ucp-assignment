#include "userinterface.h"
#include <time.h>
#include "filemanager.h"
#include <limits.h>
void userInterface(Settings* settings, LinkedList* logs)
{
    int userInput, min, max;
    min = 1;
    #ifdef EDITOR
    max = 6;
    #else
    max = 5;
    #endif

    printf("Welcome to Tic Tac Toe\n");
    do
    {
        userInput = min - 1;
        do
        {
            printf("\nPlease select from the following options\n");
            printf("1: Start a new game\n");
            printf("2: View the settings of the game\n");
            printf("3: View the current logs\n");
            #ifdef SECRET
            printf("4: Save the logs to a file(DEACTIVATED)\n");
            #else
            printf("4: Save the logs to a file\n");
            #endif
            #ifdef EDITOR
            printf("5: Change settings\n");
            printf("6: Exit the application\n");
            #else
            printf("5: Exit the application\n");
            #endif
            
            parseIntegerInput(&userInput, min, max);
        } while(userInput < min || userInput > max);

        switch(userInput)
        {
            case 1:
                game(settings, logs);
                break;
            case 2:
                viewSettings(settings);
                break;
            case 3:
                viewCurrentLogs(settings, logs); 
                break;
            case 4:
                #ifdef SECRET
                printf("ERROR: Saving logs is deactivated\n");
                #else
                saveLogsToFile(settings, logs);
                #endif
                break;
            #ifdef EDITOR
            case 5:
                changeSettings(settings);
                break;
            case 6:
                printf("Goodbye\n");
                break;
            #else
            case 5:
                printf("Goodbye\n");
                break;
            #endif
        }
    } while (userInput != max);
}

#ifdef EDITOR
void changeSettings(Settings* settings)
{
    int userInput, min, max, width, height, matching;
    int minWidth, minHeight, minMatch, maxWidth, maxHeight, maxMatch;
    min = 1;
    max = 4;
    minWidth = 0;
    minHeight = 0;
    minMatch = 1;
    maxWidth = INT_MAX;
    maxHeight = INT_MAX;
    width = -1;
    height = -1;
    matching = -1;

    /* Finds the largest of the two dimensions (as this is the max size that matching can be */
    if(settings -> width <= settings -> height)
    {
        maxMatch = settings -> height;
    }  
    else
    {
        maxMatch = settings -> width;
    }
    do
    {
        do 
        {
            printf("Please select a setting you want to change\n");
            printf("1. Width (Currently: %d)\n", settings -> width);
            printf("2. Height (Currently: %d)\n", settings -> height);
            printf("3. Matching Tiles to Win (Currently: %d)\n", settings -> matching);
            printf("4. Return to previous menu\n");

            parseIntegerInput(&userInput, min, max);
        } while((userInput < min || userInput > max));

        switch(userInput)
        {
            case 1:
                do 
                {
                    printf("Please enter a width\n");
                    parseIntegerInput(&width, minWidth, maxWidth);
                    if(width > minWidth)
                    {
                        settings -> width = width;
                    }
                    else
                    {
                        printf("ERROR: width must be between %d and %d\n", minWidth, maxWidth);
                    }
                } while((width <= minWidth || width > maxWidth));
                break;
            case 2:
                do 
                {
                    printf("Please enter a height\n");
                    parseIntegerInput(&height, minHeight, maxHeight);
                    if(height > minHeight)
                    {
                        settings -> height = height;
                    }
                    else
                    {
                        printf("ERROR: height must be above 0\n");
                    }
                } while((height <= minHeight || height > maxHeight));
                break;
            case 3:
                do 
                {
                    printf("Please enter a new amount of tiles to win\n");
                    parseIntegerInput(&matching, minMatch, maxMatch);
                    if(matching >= minMatch && matching <= maxMatch)
                    {
                        settings -> matching = matching;
                    }
                    else
                    {
                        printf("ERROR: matching must be between %d and %d", minMatch, maxMatch);
                    }
                } while((matching < minMatch || matching > maxMatch));
                break;
            case 4:
                printf("Returning to previous menu\n");
        }
    } while (userInput != max);
} 
#endif

void viewSettings(Settings* settings)
{
    printf("Settings:\n");
    printf("Width (M): %d\nHeight(N): %d\nMatching(K): %d\n", settings -> width, settings -> height, settings -> matching);
}

void viewCurrentLogs(Settings* settings, LinkedList* logs)
{
    viewSettings(settings);
    printLinkedList(logs);
}

/* Imports an integer pointer, if parses correctly from stdin, it will export the integer value, 
    otherwise it will display an error and set the integer to outside the specified range */

/* Catches invalid input such as a character is inputted 
    This is because if strtol fails to parse an integer,
    it will store the input in *ptr and will return 0
    It also checks for input such as "1b", as we check 
        that the *ptr is the value of 10 (\0 + \n) */
void parseIntegerInput(int* userInput, int min, int max)
{
    char* ptr; 
    char* input;
    input = (char*)malloc(sizeof(char) * BUFFER_SIZE); 
    if(fgets(input, BUFFER_SIZE, stdin) != NULL)
    {
        *userInput = strtol(input, &ptr, 10);

        if(*userInput == 0 && *ptr != ('\0' + '\n')) /* A number was not parsed */
        {
            /* Sets the userInput to outside the min - max range as
                the input was parsed incorrectly (i.e invalid input) */
            *userInput = min - 1;
            printf("ERROR: Please enter an integer between %d and %d\n", min, max);
        }
        else if(*ptr != ('\0' + '\n')) /* A number was parsed correctly but with trailing letters */
        {
            *userInput = min - 1;
        }
        else if(*userInput < min || *userInput > max)
        {
            printf("ERROR: Please enter an integer between %d and %d\n", min, max);
            *userInput = min - 1;
        }
    /* Checks that strtol hasn't returned 0 (will return 0 if not a numbe 
        and checks if the trailing ptr is just the value of \0 and \n
            if so this means that theres nothing behind the input,
            For example: 1a will be picked up as an invalid input */
    }
    free(input);
}

