#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Defines */
#define FALSE 0
#define TRUE !FALSE

/* Typedefs */
typedef struct {
    int width;
    int height;
    int matching;
} Settings;

/* Forward Declarations */

int settingsImport(char* fileName, Settings* settings);

#endif