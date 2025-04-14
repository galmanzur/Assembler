/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                             Print to Console Service 🖨️📜
* This file contains functions to print messages to the console.
* It includes functions to print error messages, warnings, and success messages.                                             
->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef PRINT_TO_CONSOLE_SERVICE_H
#define PRINT_TO_CONSOLE_SERVICE_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include <stdio.h>
#include "colors.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints an error message in red using printf.
 * It takes the line number and the error message as parameters. */
void print_error(int line_number, char *message);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a global error message in red using printf.
 * It takes the error message as a parameter. */
void print_global_error(char *message);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

void print_error_with_arg(int line_number, char *message_start, char *arg, char *message_end);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/ 

/* This function prints a warning message in yellow using printf.
 * It takes the line number and the warning message as parameters. */
void print_warning(int line_number, char *message);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a success message in green using printf.
 * It takes the success message as a parameter. */
void print_success(char *message);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a process file message in purple using printf.
 * It takes the file name as a parameter. */
void print_process_file(char *filename);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* PRINT_TO_CONSOLE_SERVICE_H */