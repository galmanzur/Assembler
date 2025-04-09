/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                                 Debug Service 🛠️
This file contains function for debugging purposes - it includes functions to print the symbol table.                                                
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef DEBUG_H
#define DEBUG_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "symbol_defenition.h"
#include "encoding_service.h"
#include "encoding_data.h"
#include "symbol_repo.h"
#include "file_service.h"
#include <string.h>

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints the symbol table in a structured format - for debugging or grading.
 * It takes the head of the symbol table as a parameter. */
void debug_print_symbol_table(symbol *head);

#endif /* DEBUG_H */