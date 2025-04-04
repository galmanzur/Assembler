#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include "macro_repo.h"
#include "assembler_data.h"
#include "enable_bool.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*----------------------------------------------------------------------------*/
/*funciton to spread and validate the macros in file with macros*/
void call_pre_assembler(char *input_file, char *output_file);
/*
void validate_macro_definition(FILE *src_file, macro_table *macros_list, char *word, int current_line);

void spread_out_macro(FILE *dst_file, macro_table *macros_list, char *word, char *line);*/

/*
Algorithm:
1. Checks if the macro is empty → if so, it exits immediately.
2. Adds the macro to the macro table (add_macro).
3. Frees memory for each line and the entire array.
*/
/*void save_macro(macro_table *macros_list, char **macro_lines, int num_lines);*/


#endif /* PRE_ASSEMBLER_H */


