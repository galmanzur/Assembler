/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                               Macro Repository❕
* This file contains the definition of a macro repository, which is a data structure that stores macros and their associated code lines.
* It includes functions to initialize the macro table, add macros, retrieve macros, and free the macro table.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/
#ifndef MACRO_REPO_H
#define MACRO_REPO_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "print_to_console_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This structure represents a macro, which contains of a name and an array of code lines. */
typedef struct macro
{
    char* name;
    char** lines;
    int num_lines;
} macro;

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This structure represents a macro table, which contains an array of macros,
 the number of macros, and the capacity of the macro table. */
typedef struct macro_table 
{
    macro **macros;
    int num_macros;
    int macro_capacity;
} macro_table;

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates a new macro table with the specified initial capacity. */
void init_macro_table(macro_table* macros_list);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function adds a new macro to the macro table.
 It takes a pointer to the macro table, the name of the macro, an array of code lines, and the number of lines as parameters. */
void add_macro(macro_table *macros_list, char* name, char** lines, int num_lines);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function retrieves a macro from the macro table by its name.
 It takes a pointer to the macro table and the name of the macro as parameters. */
macro *get_macro_if_equals(macro_table *macros_list, char *name);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the macro table.
 It takes a pointer to the macro table as a parameter. */
void free_macro_table(macro_table *macro_list);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* MACRO_REPO */