/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                             Pre Assembler Stage 1️⃣✔️
 * This stage is responsible for the pre-assembly process of the assembler.
    * It processes the assembly code, expands macros, and generates the pre-assembly output.
    * The stage includes functions for handling macros, validating syntax, and managing the pre-assembler process.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

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

/* This function calls the pre-assembler process. 
 * It takes the input file name and output file name as parameters.
 * It processes the output am file and expands macros.
 * It returns true if the pre-assembly was successful, false otherwise. */
bool call_pre_assembler(char *input_file, char *output_file);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* PRE_ASSEMBLER_H */


