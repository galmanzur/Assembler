#ifndef DEBUG_H
#define DEBUG_H

#include "symbol_repo.h"
#include <string.h>

/*----------------------------------------------------------------------------*/
/*function to print synbol table - not apears in use but was useful for debugging
purposes and can be used by task grader to check code correction*/
void debug_print_symbol_table(symbol *head);

#endif /* DEBUG_H */