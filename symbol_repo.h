/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                           Symbol Repository 📚
This file header contains the function declarations for managing the symbol table.
It includes functions to create, find, add, and free symbols in the symbol table.
It also includes functions to synchronize the instruction counter (IC) of data symbols and check for duplicate symbols.                                           								                                       
->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/
#ifndef SYMBOL_REPO_H
#define SYMBOL_REPO_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "symbol_defenition.h"
#include "print_to_console_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the symbol table linked list.
* It takes a pointer to the head of the symbol table as a parameter. */
void free_symbol_table(symbol *symbol_table);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates a new symbol node for the symbol table.
* It takes the name and address of the symbol as parameters and returns a pointer to the newly created symbol node. */
symbol* create_symbol(char* name, int address);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function finds a symbol in the symbol table linked list.
* It takes the head of the symbol table and the name of the symbol as parameters and returns a pointer to the found symbol node. */
symbol* find_symbol(symbol *symbol_table, char *name);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function adds a new symbol to the symbol table linked list.
 It takes a pointer to the head of the symbol table, the name of the symbol, and its address as parameters.
* It returns a pointer to the newly added symbol node. */
symbol* add_symbol(symbol **symbol_table, char *name, int address); 

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function synchronizes the instruction counter (IC) of data symbols in the symbol table.
 *It takes a pointer to the symbol table and the current IC as parameters. */
void sync_IC_of_data_symbol(symbol* symbol_table, int IC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if there are duplicate symbols in the symbol table.
* It takes a pointer to the head of the symbol table as a parameter and returns true if there are duplicate symbols, false otherwise. */
bool is_there_duplicate_symbol(symbol* head, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* SYMBOL_REPO_H */
