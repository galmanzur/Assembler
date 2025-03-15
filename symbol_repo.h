#ifndef SYMBOL_REPO_H
#define SYMBOL_REPO_H
#include "enable_bool.h"
#include "assembler_data.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* symbol structure definition */
typedef struct symbol
{
	char name[MAX_LABEL];
	int address;
	bool isExt;
	bool isEnt;
	bool isData;
	struct symbol* next;
} symbol;

/*----------------------------------------------------------------------------*/
/*function to free symbol table after we are done using it in the run*/
void free_symbol_table(symbol *symbol_table);

#endif /* SYMBOL_REPO_H */
