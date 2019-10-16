#include "userinterface.h"
#include <time.h>
void userInterface(Settings* settings)
{
    int userInput;
    char line[255];
    LinkedList* logs;
    logs = createLinkedList(logsPrinter, logsFree, logsOutputToFile);
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
                freeLinkedList(logs);
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

void saveLogsToFile(Settings* settings, LinkedList* logs)
{
    int hours, minutes, day, month;
    FILE* f;
    char fileName[50]; /* consider changing */
    /* NEED TO CHECK IF THIS IS THE PROPER WAY */
    time_t now;
    struct tm* local;
    time(&now);
    local = localtime(&now);

    hours = local -> tm_hour;
    minutes = local -> tm_min;
    day = local -> tm_mday;
    month = local -> tm_mon + 1;

    printf("Today is: %s\n", ctime(&now));

    /* NOT ENTIRELY SURE WHY BUT HOURS AND MINUTES ARE WRONG WAY ROUND */
    sprintf(fileName, "MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log", settings -> width, 
            settings -> height, settings -> matching, hours, minutes, day, month);
    f = fopen(fileName, "w");
    
    if(f != NULL)
    {
        outputListToFile(logs, f);
        fclose(f);
    }
    else
    {
        printf("FILE ERROR");
        /*perror();*/
    }
}
/*
void exitCleanup()
{
    freeLinkedList(logs);

}
*/
