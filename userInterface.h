
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
void userInterface(Settings* settings, LinkedList* logs);
void viewSettings(Settings* settings);
void viewCurrentLogs();
void changeSettings(Settings* settings);

#endif