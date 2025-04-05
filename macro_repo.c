#include "macro_repo.h"

/*----------------------------------------------------------------------------*/
void init_macro_table(macro_table* macros_list)
{
    int i; /* iterator for the loop */
    int initial_capacity = 2; /* Initial capacity for the macro list */
    
    macros_list->macros = malloc(initial_capacity * sizeof(macro));

    for (i = 0; i < initial_capacity; i++) /* Initialize each macro pointer to NULL */
        macros_list->macros[i] = NULL; 
    macros_list->num_macros = 0; /* Initialize the number of macros to 0 */
    macros_list->macro_capacity = initial_capacity; /* Set the initial capacity */
}

/*----------------------------------------------------------------------------*/
/* a fucntion to add a macro to macro list using memory allocations and strcpy of
needed fields, checks for memory availability aswell*/
void add_macro(macro_table *macros_list, char* name, char** lines, int num_lines) 
{
    int i = 0; /* iterator for the loop */
    macro* new_macro = malloc(sizeof(macro));
    if(!new_macro)
    {
        printf("CRITICAL: memory problem at add_macro\n");
        exit(EXIT_FAILURE);
    }

    if(!(new_macro->name = malloc(strlen(name) + 1)))
    {
        printf("CRITICAL: memory problem at add_macro\n");
        exit(EXIT_FAILURE);
    }

    if(!(new_macro->lines = malloc(num_lines * sizeof(char*))))
    {
        printf("CRITICAL: memory problem at add_macro\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_macro->name, name);

    for(i=0; i < num_lines; i++)
    {
        new_macro->lines[i] = malloc(strlen(lines[i]) + 1);
        strcpy(new_macro->lines[i], lines[i]);
    }
    
    /* Set the number of lines in the macro */
    new_macro->num_lines = num_lines;

    if ((macros_list->num_macros) == (macros_list->macro_capacity)) 
    {
        /* extend by multiplying by two the macro_capacity of the macro list if it's full */
        macros_list->macro_capacity *= 2;
        macros_list->macros = realloc(macros_list->macros, macros_list->macro_capacity * sizeof(macro*));

        for (i = macros_list->num_macros; i < macros_list->macro_capacity; i++) 
            macros_list->macros[i] = NULL;
    }

    /* Add the new macro to the list */
    macros_list->macros[macros_list->num_macros] = new_macro;
    macros_list->num_macros++;
}

/*----------------------------------------------------------------------------*/
/*function to get the macro from macro list*/
macro *get_macro_if_equals(macro_table *macros_list, char *name) 
{
    int i;

    if (name != NULL)
        name[strcspn(name, "\r\n")] = '\0'; /* remove newline characters */

    /* iterate through the macro list */
    for (i = 0; i < macros_list->num_macros; i++) 
    {
        char *macro_name = macros_list->macros[i]->name;

        /* remove newline characters from macro name */
        if (macro_name != NULL)
            macro_name[strcspn(macro_name, "\r\n")] = '\0';

        if (strcmp(macro_name, name) == 0) 
        {
            return macros_list->macros[i];
        } 
    }

    return NULL;
}

/*----------------------------------------------------------------------------*/
/*a function to destroy table*/
void free_macro_table(macro_table *macro_list)
{
    int i, j;
    
    for(i = 0; i < macro_list->num_macros ;i++) /* Loop over all macros in the table */
    {
        macro* curr_macro = macro_list->macros[i];
        free(curr_macro->name);
        for (j = 0; j < curr_macro->num_lines ;j++)
            free(curr_macro->lines[j]);
        free(curr_macro->lines);
        free(curr_macro);
    }

    free(macro_list->macros);
    macro_list->num_macros = 0;
    macro_list->macro_capacity = 0;
}

/*
 * This function prints all macros in the given macro_table,
 * including their names, number of lines, and the lines themselves.
 */
void print_macro_table(macro_table *table)
{
    int i, j;
    
    /* Check if the macro table is NULL */
    if (table == NULL)
    {
        printf("Macro table pointer is NULL.\n");
        return;
    }

    printf("=== Macro Table ===\n");
    printf("Number of macros: %d\n", table->num_macros);

    /* Loop over all macros in the table */
    for (i = 0; i < table->num_macros; i++)
    {
        macro *m = table->macros[i];

        if (m != NULL)
        {
            printf("\nMacro %d:\n", i + 1);
            printf("  Name: %s\n", m->name);
            printf("  Number of lines: %d\n", m->num_lines);
            printf("  Lines:\n");
            
            for (j = 0; j < m->num_lines; j++)
            {
                printf("    %s\n", m->lines[j]);
            }
        }
        else
        {
            /* If for some reason the macro pointer is NULL */
            printf("\nMacro %d is NULL.\n", i + 1);
        }
    }

    printf("\n=== End of Macro Table ===\n");
}