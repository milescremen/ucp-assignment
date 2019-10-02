#include "tictactoe.h"
#include "userInterface.h"
int main(int argc, char* argv[])
{
    int width, height, matching;
    int error;
    error = FALSE;

    /* Checks correct amount of command line arguments. If it fails, it will
        print out an error and exit */
    if(argc == 2)
    {
        error = settingsImport(argv[1], &width, &height, &matching);
        if(error == FALSE)
        {
            userInterface(width, height, matching);
        }
    }
    else
    {
        printf("ERROR: Invalid amount of arguments, exiting..\n");
        error = TRUE;
    }
    return error;
}

/* Imports the address of the setting variables, so they can be set without returning
    will return 0, if no errors are occured */
int settingsImport(char* fileName, int* width, int* height, int* matching)
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
                    if((value >= 1) && (widthBool == FALSE)) /* Minimum of 1 column */
                    {
                        *width = value;
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
                    if((value >= 1) && (heightBool == FALSE))/* Minimum of 1 row */
                    {
                        *height = value;
                        widthBool = TRUE; /* sets bool to true, so duplicates dont occur */
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
                    if((value >= 2) && (matchingBool == FALSE)) /* Minimum of two matching tiles */
                    {
                        *matching = value;
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
        ferror(f);
        error = TRUE;
    }
    return error;
}



