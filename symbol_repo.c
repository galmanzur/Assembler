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