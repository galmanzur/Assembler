#include "macro_repo.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates a new macro table with the specified initial capacity. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function adds a new macro to the macro table.
 It takes a pointer to the macro table, the name of the macro, an array of code lines, and the number of lines as parameters. */
void add_macro(macro_table *macros_list, char* name, char** lines, int num_lines) 
{
    int i = 0; /* iterator for the loop */
    macro* new_macro = malloc(sizeof(macro));
    if(!new_macro)
    {
        print_global_error("Memory problem at add_macro");
        exit(EXIT_FAILURE);
    }

    if(!(new_macro->name = malloc(strlen(name) + 1)))
    {
        print_global_error("Memory problem at add_macro");
        exit(EXIT_FAILURE);
    }

    if(!(new_macro->lines = malloc(num_lines * sizeof(char*))))
    {
        print_global_error("Memory problem at add_macro");
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function retrieves a macro from the macro table by its name.
 It takes a pointer to the macro table and the name of the macro as parameters. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the macro table.
 It takes a pointer to the macro table as a parameter. */
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
