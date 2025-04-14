#ifndef TECHNICAL_FUNCTIONS_H
#define TECHNICAL_FUNCTIONS_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "print_to_console_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function extracts the parameters from a line of code and stores them in a new buffer.
* It takes the original line, the current line number, and the new buffer as parameters. */
void extract_params(char buffer[], char new_buffer[]);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function removes the label from a line of code if present.
* It takes the line as a parameter and returns the line without the label. */
char* remove_label(char* line);

#endif /* TECHNICAL_FUNCTIONS_H */