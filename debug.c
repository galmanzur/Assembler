#include "debug.h"

/*function to print symbol table linked list - was used for debugging and can be
used by task grader for checking correction of symbol table*/
void debug_print_symbol_table(symbol *head)
{
    symbol *current = head;

    printf("--------------------------------Symbol Table----------------------------------------------------:\n");
    printf("%-30s %-10s %-10s %-10s %-10s %s\n", "Name", "Address", "External", "Entry", "Data", "Next");

    while (current != NULL)
    {
        printf("%-30s %-10d %-10s %-10s %-10s %u\n",
                current->name,
                current->address,
                current->isExternal ? "Yes" : "No",
                current->isEntry ? "Yes" : "No",
                current->isData ? "Yes" : "No",
                (unsigned)current->next);
        current = current->next;
    }
    printf("-------------------------------------------------------------------------------------------------:\n");
}


