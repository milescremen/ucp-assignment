
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "game.h"

/* Defines */
#define FALSE 0
#define TRUE !FALSE

/* Typedefs */

/* Forward Declarations */
void userInterface(Settings* settings);
void viewSettings(Settings* settings);
void viewCurrentLogs();
void saveLogsToFile();
#endif