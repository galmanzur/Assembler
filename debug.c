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
                current->isExt ? "Yes" : "No",
                current->isEnt ? "Yes" : "No",
                current->isData ? "Yes" : "No",
                (unsigned)current->next);
        current = current->next;
    }

    printf("-------------------------------------------------------------------------------------------------:\n");
}

/**
 * Prints the contents of the codeimage linked list for debugging.
 * Each instruction word is printed in binary and hexadecimal formats.
 *
 * @param head - pointer to the first node in the codeimage list
 */
void print_codeimage_debug(codeimage* head_code_image) {
    int IC = 100; /* Instruction Counter starts from 100 */
    int i;
    int j;

    printf("------------ CODE IMAGE DEBUG START ------------\n");

    while (head_code_image) {
        for (i = 0; i < head_code_image->number_of_words && i < 200; i++) {
            unsigned int word = head_code_image->encoded_instruction[i].bit;

            /* Print address */
            printf("IC: %03d\t", IC++);

            /* Print binary representation using . and / (optional: change to 0/1 if needed) */
            for (j = 13; j >= 0; j--) {
                printf("%c", ((word >> j) & 1) ? '1' : '0');
            }

            /* Print actual hexadecimal value for clarity */
            printf("   (hex: 0x%04X)\n", word);
        }
        head_code_image = head_code_image->next;
    }

    printf("------------- CODE IMAGE DEBUG END -------------\n");
}

