#include "userinterface.h"
#include <time.h>
#include "filemanager.h"
void userInterface(Settings* settings, LinkedList* logs)
{
    int userInput;
    char line[255];
    printf("Welcome to Tic Tac Toe\n");
    do
    {
        do
        {
            printf("\nPlease select from the following options\n");
            printf("1: Start a new game\n");
            printf("2: View the settings of the game\n");
            printf("3: View the current logs\n");
            printf("4: Save the logs to a file\n");
            printf("5: Exit the application\n");
/*            nRead = scanf("%d", &userInput);
            if(nRead != 1)
            {
                printf("Error, please enter an integer");
            }
*/           
            if(fgets(line, 255, stdin) != NULL)
            {
                userInput = atoi(line);
            }
            else
            {
                printf("Error, please enter an integer");
            }
        } while((userInput < 1 || userInput > 5));

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
                saveLogsToFile(settings, logs);
                break;
            case 5:
                printf("Goodbye\n");
                break;
        }
    } while(userInput != 5);
}

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

