#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "macro_repo.h"
#include "enable_bool.h"
#include "print_to_console_service.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#define START_DEFINE_MACRO_WORD "mcro" 
#define END_DEFINE_MACRO_WORD "mcroend" 

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/*funciton to spread and validate the macros in file with macros*/
bool call_pre_assembler(char *input_file, char *output_file);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* PRE_ASSEMBLER_H */


