

void userInterface(int* width, int* height, int* matching)
{
    printf("Welcome to Tic Tac Toe\n");
    do
    {
        printf("Please select from the following options\n" 
                + "1: Start a new game\n"
                + "2: View the settings of the game\n"
                + "3: View the current logs\n"
                + "4: Save the logs to a file\n"
                + "5: Exit the application\n");
        nRead = scanf("%d", userInput);
        if(nRead != 1)
        {
            printf("Error, please enter an integer");
        }
    } while((userInput < min || userInput > max) && nRead == 1);

    switch(userInput)
    {
        case 1:

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
        default:
    }
}

void viewSettings(int* width, int* height, int* matching)
{
    printf("Settings:\n");
    printf("Width (M): " + width + "\nHeight (N): " + height + "\nMatching (K): " + matching + "\n"); 
}



