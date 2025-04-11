/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                             Print to Console Service 🖨️📜
This file contains functions to print messages to the console.
It includes functions to print error messages, warnings, and success messages.                                             
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef PRINT_TO_CONSOLE_SERVICE_H
#define PRINT_TO_CONSOLE_SERVICE_H

#include <stdio.h>
#include "colors.h"


void print_error(int line, char *message);

void print_global_error(char *message);

void print_warning(int line, char *message);

void print_success(char *message);

void print_process_file(char *filename);

#endif /* PRINT_TO_CONSOLE_SERVICE_H */