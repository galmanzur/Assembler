#ifndef SYMBOL_REPO_H
#define SYMBOL_REPO_H

#include "enable_bool.h"
#include "parser.h"
#include "assembler_config_data.h"
#include "addressing_service.h"
#include "encoding_service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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
void update_symbol_address(symbol* symbol_table, int IC);

/*----------------------------------------------------------------------------*/
/*function to itterate through symbol tbale linked list and check if lable has been 
defined twice for error handling after first pass*/
bool is_there_duplicate_symbol(symbol* head);

#endif /* SYMBOL_REPO_H */
