#include "userInterface.h"
void userInterface(int width, int height, int matching)
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
                game(width, height, matching);
                break;
            case 2:
                viewSettings(width, height, matching);
                break;
            case 3:
                viewCurrentLogs(); 
                break;
            case 4:
                saveLogsToFile();
                break;
            case 5:
                printf("Goodbye\n");
                break;
        }
    } while(userInput != 5);
}

void viewSettings(int width, int height, int matching)
{
    printf("Settings:\n");
    printf("Width (M): %d\nHeight(N): %d\nMatching(K): %d\n", width, height, matching);
}

void viewCurrentLogs()
{
    printf("Not implemented yet");
}

void saveLogsToFile()
{
    printf("Not implemented yet");
}
