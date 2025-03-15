#include "macro_repo.h"

/*----------------------------------------------------------------------------*/
void init_macro_table(macro_table* macros_list)
{
    int i;
    int initial_capacity = 2; /*initial size of macros in macro table for memory efficency*/
    macros_list->macros = malloc(initial_capacity * sizeof(macro));
    for (i = 0; i < initial_capacity; i++) 
        macros_list->macros[i] = NULL;
    macros_list->num_macros = 0;
    macros_list->macro_capacity = initial_capacity;
}

/*----------------------------------------------------------------------------*/
/* a fucntion to add a macro to macro list using memory allocations and strcpy of
needed fields, checks for memory availability aswell*/
void add_macro(macro_table *macros_list, char* name, char** lines, int num_lines) 
{
    int i = 0;
    macro* new_macro = malloc(sizeof(macro));
    if(!new_macro)
    {
        printf("CRITICAL: MEMORY PROBLEM!!!\n");
        exit(EXIT_FAILURE);
    }
    if(!(new_macro->name = malloc(strlen(name) + 1)))
    {
        printf("CRITICAL: MEMORY PROBLEM!!!\n");
        exit(EXIT_FAILURE);
    }
    if(!(new_macro->lines = malloc(num_lines * sizeof(char*))))
    {
        printf("CRITICAL: MEMORY PROBLEM!!!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_macro->name, name);
    for(i=0; i < num_lines; i++)
    {
        new_macro->lines[i] = malloc(strlen(lines[i]) + 1);
        strcpy(new_macro->lines[i], lines[i]);
    }
    
    new_macro->num_lines = num_lines;
    if ((macros_list->num_macros) == (macros_list->macro_capacity)) 
    {
        /* extend by multiplying by two the macro_capacity of the macro list if it's full */
        macros_list->macro_capacity *= 2;
        macros_list->macros = realloc(macros_list->macros, macros_list->macro_capacity * sizeof(macro*));
        for (i = macros_list->num_macros; i < macros_list->macro_capacity; i++) 
            macros_list->macros[i] = NULL;
    }
    macros_list->macros[macros_list->num_macros] = new_macro;
    macros_list->num_macros++;
}

/*----------------------------------------------------------------------------*/
/*function to get the macro from macro list*/
macro *get_macro(macro_table *macros_list, char *name) 
{
    int i;
    /*ittireating through the loop to find macro*/
    for (i = 0; i < macros_list->num_macros; i++) 
    {
        if (strcmp(macros_list->macros[i]->name, name) == 0) 
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
    for(i = 0; i < macro_list->num_macros ;i++)
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
