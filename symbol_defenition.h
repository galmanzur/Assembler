/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                           Symbol Definition ✏️
This file header defines the structure of a symbol in the symbol table.										                                       
->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/
#ifndef SYMBOL_DEFENITION_H
#define SYMBOL_DEFENITION_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "enable_bool.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This struct defines a symbol in the symbol table.
 * It contains the name of the symbol, its address, and flags indicating if it is external, entry, or data.
 * It also contains a pointer to the next symbol in the linked list. 
 * The name is defined as a constant with a maximum length of characters.  */
typedef struct symbol
{
	char name[MAX_LENGTH_LABEL];
	int address;
	bool isExternal;
	bool isEntry;
	bool isData;
	struct symbol* next;
} symbol;

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* SYMBOL_DEFENITION_H */