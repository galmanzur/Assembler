/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                               First Pass Stage 1️⃣✔️
 * This stage is responsible for the first pass of the assembler.
 * It processes the assembly code, validates the syntax, and builds the symbol table.
 * The stage includes functions for validating lines, handling labels, and processing directives.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef FIRST_PASS_H
#define FIRST_PASS_H
/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "encoding_data.h"
#include "technical_functions.h"
#include "symbol_repo.h"
#include "enable_bool.h"
#include "parser.h" 
#include "file_service.h"
#include "addressing_service.h"
#include "process_data.h"
#include "print_to_console_service.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function performs the first pass of the assembler. 
 * It processes the assembly code, validates the syntax, and builds the symbol table.
 * It takes the symbol table, file name, instruction counter (IC), and data counter (DC) as parameters.
 * It returns true if the first pass was successful, false otherwise. */
bool call_first_pass(symbol** symbol_table, char *filename, int *IC, int *DC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function validate the line syntax in the assembly language.
 * It takes the line, current line number (current_line), data counter (DC), and symbol table as parameters.
 * It returns true if the line is valid, false otherwise. */
bool validate_all_in_line(char* line, int current_line, int *DC, symbol** symbol_table);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function validate that there is a space after the data or string directive in the line.
 * It takes the line and current line number (current_line) as parameters.
 * It returns true if pass the validation, false otherwise. */
bool validate_space_after_data_or_string(char line[], int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* FIRST_PASS_H */