#include "filemanager.h"
#include "userinterface.h"
/* PROBS CREATE THE LOGS IN MAIN? NOT USER INTERFACE IDK */
int main(int argc, char* argv[])
{
    Settings* settings;
    int error;
    error = FALSE;

    /* Checks correct amount of command line arguments. If it fails, it will
        print out an error and exit */
    if(argc == 2)
    {
        settings = (Settings*)malloc(sizeof(Settings));
        error = settingsImport(argv[1], settings);
        if(error == FALSE)
        {
            userInterface(settings);
        }
        free(settings);
    }
    else
    {
        printf("ERROR: Invalid amount of arguments, exiting..\n");
        error = TRUE;
    }
    return error;
}



