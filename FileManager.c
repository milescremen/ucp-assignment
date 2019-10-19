#include "filemanager.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <time.h>

/* Imports the address of the setting variables, so they can be set without returning
    will return 0, if no errors are occured */
int settingsImport(char* fileName, Settings* settings)
{
    FILE* f;
    char setting; 
    int value, nRead;
    int widthBool, heightBool, matchingBool; /* Used for checking for duplicates */
    int error; /* Returns 0 if file is read correctly */

    widthBool = FALSE;
    heightBool = FALSE;
    matchingBool = FALSE;

    error = FALSE;
    f = fopen(fileName, "r"); /* r flag for reading the file */

    /* Checks if file opened, otherwise will print an error and exit */
    if(f != NULL)
    {
        do
        {
            nRead = fscanf(f,"%c=%d\n", &setting, &value);
            printf("%c %d\n", setting, value);

            /* Checks if line was valid */
            if(nRead == 2)
            {
                if(setting == 'M' || setting == 'm')
                {
                    if((value > 0) && (widthBool == FALSE)) /* Minimum of 1 column */
                    {
                        settings -> width = value;
                        widthBool = TRUE;
                    }
                    else if(widthBool == TRUE)
                    {
                        printf("ERROR: Duplicate width in file\n");
                        error = TRUE;
                    }
                    else
                    {
                        printf("ERROR: Invalid width setting\n");
                        error = TRUE;
                    }
                }
                else if(setting == 'N' || setting == 'n')
                {
                    if((value > 0) && (heightBool == FALSE))/* Minimum of 1 row */
                    {
                        settings -> height = value;
                        heightBool = TRUE; /* sets bool to true, so duplicates dont occur */
                    }
                    else if(heightBool == TRUE)
                    {
                        printf("ERROR: Duplicate height setting in file\n");
                        error = TRUE;
                    }
                    else
                    {
                        printf("ERROR: Invalid height setting\n");
                        error = TRUE;
                    }  
                }
                else if(setting == 'K' || setting == 'k')
                {
                    if((value > 1) && (matchingBool == FALSE)) 
                    {
                        settings -> matching = value;
                        matchingBool = TRUE;
                    }
                    else if(matchingBool == TRUE)
                    {
                        printf("ERROR: Duplicate matching setting in file\n");
                        error = TRUE;
                    }
                    else
                    {
                        printf("ERROR: Invalid matching setting\n");
                        error = TRUE;
                    }
                }
                else
                {
                    printf("ERROR: Invalid setting\n");
                    error = TRUE;
                }
            }
            else
            {
                printf("ERROR: Invalid line\n");
                error = TRUE;
            }
        } while(!feof(f) && error == FALSE);
        fclose(f);
    }  
    else
    {
        /* perror(f); */
        error = TRUE;
    }
    return error;
}

void saveLogsToFile(Settings* settings, LinkedList* logs)
{
    int hours, minutes, day, month;
    FILE* f;
    char fileName[50]; /* consider changing */
    /* NEED TO CHECK IF THIS IS THE PROPER WAY */
    time_t now;
    struct tm* local;
    Node* currentNode;
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

        currentNode = logs -> head;

        while(currentNode != NULL)
        {
            (*logs -> outputFunc)(currentNode -> data, f);
            currentNode = currentNode -> next;
        }
        fclose(f);
    }
    else
    {
        printf("FILE ERROR");
        /*perror();*/
    }
}
