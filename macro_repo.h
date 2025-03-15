#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*----------------------------------------------------------------------------*/
/*defining a struct for macro*/
typedef struct macro
{
    char* name;
    char** lines;
    int num_lines;
} macro;

/*----------------------------------------------------------------------------*/
/* define a structure for a macros list */
typedef struct macro_table 
{
    macro **macros;
    int num_macros;
    int macro_capacity;
} macro_table;

/*----------------------------------------------------------------------------*/
/*function to init macro table at the beginning of the spread macto phase*/
void init_macro_table(macro_table* macros_list);

/*----------------------------------------------------------------------------*/
/*function to add macro to the macro table struct with all the relevant code 
lines before it is being spread*/
void add_macro(macro_table *macros_list, char* name, char** lines, int num_lines);

/*----------------------------------------------------------------------------*/
/*function to get macro and its relevant code lines before spreading it to the 
.am filre for encodeing*/
macro *get_macro(macro_table *macros_list, char *name);

/*----------------------------------------------------------------------------*/
/*function to free and destroy the macro table after it is being used*/
void free_macro_table(macro_table *macro_list);

#endif /* FILE_SERVICE_H */