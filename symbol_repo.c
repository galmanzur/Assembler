#include "symbol_repo.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the symbol table linked list.
* It takes a pointer to the head of the symbol table as a parameter. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates a new symbol node for the symbol table.
* It takes the name and address of the symbol as parameters and returns a pointer to the newly created symbol node. */
symbol* create_symbol(char* name, int address) 
{
    symbol* new_symbol = (symbol*) malloc(sizeof(symbol));
    strncpy(new_symbol->name, name, MAX_LENGTH_LABEL);
    new_symbol->address = address;
    new_symbol->isExternal = false;
    new_symbol->isEntry = false;
    new_symbol->isData = false;
    new_symbol->next = NULL;
    return new_symbol;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/


/* This function finds a symbol in the symbol table linked list.
* It takes the head of the symbol table and the name of the symbol as parameters and returns a pointer to the found symbol node. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function adds a new symbol to the symbol table linked list.
* It takes a pointer to the head of the symbol table, the name of the symbol, and its address as parameters.
* It returns a pointer to the newly added symbol node. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function synchronizes the instruction counter (IC) of data symbols in the symbol table.
* It takes a pointer to the symbol table and the current IC as parameters. */
void sync_IC_of_data_symbol(symbol* symbol_table, int IC)
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if there are duplicate symbols in the symbol table.
* It takes a pointer to the head of the symbol table as a parameter and returns true if there are duplicate symbols, false otherwise. */
bool is_there_duplicate_symbol(symbol* head, int current_line) 
{
    symbol* curr = head;

    while (curr != NULL) {
        symbol* temp = curr->next;
        while (temp != NULL) 
        {
            if (strcmp(curr->name, temp->name) == 0) 
            {
                print_error_with_arg(current_line, "Duplicate label", curr->name, "is defined." );
                return true;
            }
            temp = temp->next;
        }
        curr = curr->next;
    }
    return false;
}
