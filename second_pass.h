/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                             Second Pass Stage  2️⃣✔️
* This stage is responsible for the second pass of the assembler.
* It processes the assembly code, encodes the instructions and data, and generates the final object file.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef SECOND_PASS_H
#define SECOND_PASS_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "file_service.h"
#include "encoding_service.h"
#include "enable_bool.h"
#include "encoding_repo.h"
#include "addressing_service.h"
#include "parser.h"
#include "encoding_data.h"
#include "symbol_defenition.h"
#include "print_to_console_service.h"
#include "encoding_data.h"
#include "debug.h"
#include <stdio.h>

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function is responsible for the second pass of the assembler. 
 * It processes the assembly code, encodes the instructions and data, and generates the final object file.
 * It takes the file name, current code image node, symbol table, instruction counter (IC), data counter (DC), data image array, and extern list as parameters.
 * It returns true if the second pass was successful, false otherwise. */
bool call_second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* SECOND_PASS_H */
