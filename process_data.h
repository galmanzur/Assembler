/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                           Process Data 🛠️
* This file contains functions to process lines of code in the assemble - it can be opcode, or directive.
* It includes functions to process all line, handle string and data directives.
* The functions are used to validate the syntax of the data directives and add them to the symbol table.                                       
->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "enable_bool.h"
#include "symbol_defenition.h"
#include "symbol_repo.h"
#include "parser.h"
#include "technical_functions.h"
#include "print_to_console_service.h"
#include <stdio.h>
#include <string.h>
/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function processes a line of code and handles the string directive statement.
 * It takes the string, current line number, and data counter as parameters.
 * It returns true if the processing was successful, false otherwise. */
int handle_string_directive_statement(char *str, int current_line, int *DC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function processes a line of code and handles the string directive statement.
 * It takes the string, current line number, and data counter as parameters.
 * It returns true if the processing was successful, false otherwise. */
int handle_data_directive_statement(char* line, int current_line, int *DC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function processes a line - it checks if line is opcode or directive and handles it accordingly.
 * It returns true if the processing was successful, false otherwise. */
bool process_line(char* line, int current_line, symbol** symbol_table, int *IC, int *DC);

#endif/* PROCESS_DATA_H */