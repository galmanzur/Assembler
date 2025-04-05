#ifndef SYMBOL_REPO_H
#define SYMBOL_REPO_H

#include "symbol_defenition.h"

/*----------------------------------------------------------------------------*/
/*function to free symbol table after we are done using it in the run*/
void free_symbol_table(symbol *symbol_table);

/*----------------------------------------------------------------------------*/
/*function to create a symbol with all its data*/
symbol* create_symbol(char* name, int address);

/*----------------------------------------------------------------------------*/
/*function to find symbol in table*/
symbol* find_symbol(symbol *symbol_table, char *name);

/*----------------------------------------------------------------------------*/
/*function to add synbol to synbol table linked list*/
symbol* add_symbol(symbol **symbol_table, char *name, int address); 

/*----------------------------------------------------------------------------*/
/*function to update symbol of data lables in the symbol table becuase IC and DC
does not increments simultanisaly but should be printed together*/
void sync_IC_of_data_symbol(symbol* symbol_table, int IC);

/*----------------------------------------------------------------------------*/
/*function to itterate through symbol tbale linked list and check if lable has been 
defined twice for error handling after first pass*/
bool is_there_duplicate_symbol(symbol* head);

#endif /* SYMBOL_REPO_H */
