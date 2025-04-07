#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "manager.h"
#include "encoding_data.h"
#include "technical_functions.h"
#include "symbol_repo.h"
#include "enable_bool.h"
#include "parser.h" 
#include "file_service.h"
#include "addressing_service.h"
#include "process_data.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------*/
/*function to handle the first pass of this two pass assembler*/
bool call_first_pass(symbol** symbol_table, char *filename, int *IC, int *DC);

/*----------------------------------------------------------------------------*/
/*function to validate line syntax*/
bool validate_all_in_line(char* line, int cline, int *DC, symbol** symbol_table);

/*----------------------------------------------------------------------------*/
/*a function assuming only .data or .string can apear in line 
validating if the instruction is seperated by space*/
bool validate_space_after_data_or_string(char line[], int cline);

/*----------------------------------------------------------------------------*/
/*assuming : exist beacuse was handled before hand*/
char validate_entry_extern_after_label(char line[], int cline);

#endif /* FIRST_PASS_H */