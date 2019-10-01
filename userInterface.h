
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

/* Defines */
#define FALSE 0
#define TRUE !FALSE

/* Typedefs */

/* Forward Declarations */
void userInterface(int width, int height, int matching);
void viewSettings(int width, int height, int matching);
void viewCurrentLogs();
void saveLogsToFile();
#endif