#include "filemanager.h"
#include "userinterface.h"
/* PROBS CREATE THE LOGS IN MAIN? NOT USER INTERFACE IDK */
int main(int argc, char* argv[])
{
    Settings* settings;
    LinkedList* logs;
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
            logs = createLinkedList(logsPrinter, logsFree, logsFileFunc);
            userInterface(settings, logs);
        }

        freeLinkedList(logs);
        free(settings);
    }
    else
    {
        printf("ERROR: Invalid amount of arguments, exiting..\n");
        error = TRUE;
    }
    return error;
}



