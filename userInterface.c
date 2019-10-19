#include "userinterface.h"
#include <time.h>
#include "filemanager.h"
void userInterface(Settings* settings, LinkedList* logs)
{
    int userInput, min, max;
    int error;
    char* input;
    char* ptr; 
    min = 1;
    #ifdef EDITOR
    max = 6;
    #else
    max = 5;
    #endif

    input = (char*)malloc(sizeof(char) * 255); 
    printf("Welcome to Tic Tac Toe\n");
    do
    {
        error = FALSE;
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
            
            if(fgets(input, 255, stdin) != NULL)
            {
                if(input[255 - 1] != '\n')
                {
                    userInput = strtol(input, &ptr, 10);
                }
                else
                {
                    input = NULL;
                }
                /* Checks that strtol hasn't returned 0 (will return 0 if not a numbe 
                    and checks if the trailing ptr is just the value of \0 and \n
                        if so this means that theres nothing behind the input,
                        For example: 1a will be picked up as an invalid input */
                if(userInput != 0 && *ptr != ('\0' + '\n'))
                {
                    error = TRUE;
                    printf("ERROR: Please enter an integer between %d and %d\n", min, max);
                }
            }
        } while((userInput < min || userInput > max || error == TRUE));

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
    char line[255];
    min = 1;
    max = 4;
    do
    {
        printf("Please select a setting you want to change\n");
        printf("1. Width (Currently: %d)\n", settings -> width);
        printf("2. Height (Currently: %d)\n", settings -> height);
        printf("3. Matching Tiles to Win (Currently: %d)\n", settings -> matching);
        printf("4. Return to previous menu\n");
        do 
        {
            if(fgets(line, 255, stdin) != NULL)
            {
                userInput = atoi(line);
            }
            else
            {
                printf("Error, please enter an integer");
            }
        } while((userInput < min || userInput > max));

        switch(userInput)
        {
            case 1:
                printf("Please enter a width\n");
                do 
                {
                    if(fgets(line, 255, stdin) != NULL)
                    {
                        width = atoi(line);
                        if(width >= 0)
                        {
                            settings -> width = width;
                        }
                        else
                        {
                            printf("ERROR: Width must be above 0");
                        }
                    }
                    else
                    {
                        printf("Error, please enter an integer");
                    }
                } while((width <= 0));
                break;
            case 2:
                printf("Please enter a height\n");
                do 
                {
                    if(fgets(line, 255, stdin) != NULL)
                    {
                        height = atoi(line);
                        if(height >= 0)
                        {
                            settings -> height = height;
                        }
                        else
                        {
                            printf("ERROR: height must be above 0");
                        }
                    }
                    else
                    {
                        printf("Error, please enter an integer");
                    }
                } while((height <= 0));
                break;
            case 3:
                printf("Please enter a new amount of tiles to win\n");
                do 
                {
                    if(fgets(line, 255, stdin) != NULL)
                    {
                        matching = atoi(line);
                        if(matching >= 0)
                        {
                            settings -> matching = matching;
                        }
                        else
                        {
                            printf("ERROR: height must be above 0");
                        }
                    }
                    else
                    {
                        printf("Error, please enter an integer");
                    }
                } while((userInput <= 0));
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

