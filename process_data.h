#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H
#include "manager.h"
#include "assembler_data.h"
#include "enable_bool.h"
#include "symbol_repo.h"
#include "technical_functions.h"

/*----------------------------------------------------------------------------*/
/*a fucntion to validate a string strats and ends with ", and the charactets
inside the "" are all ascii, gets string and line
assuming we get string parameter*/
int handle_string_statement(char *str, int cline, int *DC);

/*----------------------------------------------------------------------------*/
/*assuming opcode was handled before hand and already checked for unnecessary 
comma at the beginning and end of line, line is destructable
function to validate a data parameter */
int handle_data_statement(char* line, int cline, int *DC);

/*----------------------------------------------------------------------------*/
/*function to add line synbol to symbol table*/
bool handle_symbol_in_line(char* line, int cline, symbol** symbol_table, int *IC, int *DC);

#endif/* PROCESS_DATA_H */