#include "symbol_repo.h"

/*----------------------------------------------------------------------------*/
/* a function to free symbol table after we done using it*/
void free_symbol_table(symbol *symbol_table)
{
    symbol *current = symbol_table;
    symbol *temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}

/*----------------------------------------------------------------------------*/
/*function to create a symbol with all its data before filling*/
symbol* create_symbol(char* name, int address) 
{
    symbol* new_symbol = (symbol*) malloc(sizeof(symbol));
    strncpy(new_symbol->name, name, MAX_LABEL);
    new_symbol->address = address;
    new_symbol->isExt = false;
    new_symbol->isEnt = false;
    new_symbol->isData = false;
    new_symbol->next = NULL;
    return new_symbol;
}

/*----------------------------------------------------------------------------*/
/*function to find symbol in symbol table*/
symbol* find_symbol(symbol *symbol_table, char *name) 
{
    symbol *current = symbol_table;
    if(name)
    {
        while (current != NULL) 
        {
            if (strcmp(current->name, name) == 0) 
            {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

/*----------------------------------------------------------------------------*/
/*function to add symbol to symbol table linked list*/
symbol* add_symbol(symbol **symbol_table, char *name, int address)
{
    symbol *new_symbol = create_symbol(name, address);

    if (*symbol_table == NULL)
        *symbol_table = new_symbol;
    else
    {
        new_symbol->next = *symbol_table;
        *symbol_table = new_symbol;
    }
    return new_symbol;
}

/*----------------------------------------------------------------------------*/

/*function to update data symbols because DC and IC are not counted simulatinsely*/
void update_symbol_address(symbol* symbol_table, int IC)
{
    symbol* current = symbol_table;

    while (current != NULL)
    {
        if (current->isData == true) {
            current->address += IC;
        }
        current = current->next;
    }
}

 /*----------------------------------------------------------------------------*/
/*function to check if label appears twice in the symbol table which is not a valid*/
bool is_there_duplicate_symbol(symbol* head) 
{
    symbol* curr = head;

    while (curr != NULL) {
        symbol* temp = curr->next;
        while (temp != NULL) 
        {
            if (strcmp(curr->name, temp->name) == 0) {
                printf("Error: Duplicate label '%s'\n", curr->name);
                return true;
            }
            temp = temp->next;
        }
        curr = curr->next;
    }
    return false;
}
