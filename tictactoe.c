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
    char* setting; /* read only string as don't need to edit, also don't want to assume its size one and then get a segfault*/
    int value, nRead;
    int widthBool, heightBool, matchingBool; /* Used for checking for duplicates */
    int error; /* Returns 0 if file is read correctly */

    widthBool = FALSE;
    heightBool = FALSE;
    matchingBool = FALSE;
    setting = NULL; /* Need to initalize this otherwise compiler complains */

    error = FALSE;
    f = fopen(fileName, "r"); /* r flag for reading the file */

    /* Checks if file opened, otherwise will print an error and exit */
    if(f != NULL)
    {
        while(!feof(f) && error == FALSE)
        {
            nRead = fscanf(f,"%s=%d\n", setting, &value);
            printf("%d", nRead);

            /* Checks if line was valid */
            if(nRead == 2)
            {
                if(strcmp(setting, "M") == 0)
                {
                    if((value >= 1) && (widthBool == FALSE)) /* Minimum of 1 column */
                    {
                        *width = value;
                        widthBool = TRUE;
                    }
                    else
                    {
                        printf("Duplicate width in file\n");
                        error = TRUE;
                    }
                }
                else if(strcmp(setting, "N") == 0)
                {
                    if((value >= 1) && (heightBool == FALSE))/* Minimum of 1 row */
                    {
                        *height = value;
                        widthBool = TRUE; /* sets bool to true, so duplicates dont occur */
                    }
                    else
                    {
                        printf("Duplicate height setting file\n");
                        error = TRUE;
                    }   
                }
                else if(strcmp(setting, "K") == 0)
                {
                    if((value >= 2) && (matchingBool == FALSE)) /* Minimum of two matching tiles */
                    {
                        *matching = value;
                        matchingBool = TRUE;
                    }
                }
                else
                {
                    printf("Invalid setting\n");
                    error = TRUE;
                }
            }
            else
            {
                printf("Invalid line\n");
                error = TRUE;
            }
        }
        fclose(f);
    }  
    else
    {
        ferror(f);
        error = TRUE;
    }
    return error;
}



