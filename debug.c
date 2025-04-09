#include "debug.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints the symbol table in a structured format - for debugging or grading.
 * It takes the head of the symbol table as a parameter. */
void debug_print_symbol_table(symbol *head)
{
    symbol *current = head;
    int index = 0;

    printf("\n========================= Symbol Table =========================\n");
    printf("| %-3s | %-20s | %-7s | %-7s | %-6s | %-7s |\n", "i", "Name", "Address", "External", "Entry", "Data");
    printf("----------------------------------------------------------------\n");

    while (current != NULL)
    {
        printf("| %-3d | %-20s | %-7d | %-7s | %-6s | %-7s |\n",
               index++,
               current->name,
               current->address,
               current->isExternal ? "Yes" : "No",
               current->isEntry ? "Yes" : "No",
               current->isData ? "Yes" : "No");
        current = current->next;
    }
    printf("================================================================\n");
}
