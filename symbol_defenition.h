#ifndef SYMBOL_DEFENITION_H
#define SYMBOL_DEFENITION_H

#include "manager.h"
#include "enable_bool.h"

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

#endif /* SYMBOL_DEFENITION_H */