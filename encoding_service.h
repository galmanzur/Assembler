#ifndef ENCODING_SERVICE_H
#define ENCODING_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "manager.h"
#include "addressing_service.h"
#include "encoding_data.h"
#include "symbol_repo.h"
#include "second_pass.h"
#include "enable_bool.h"
#include "technical_functions.h"
#include "print_to_console_service.h"

/* *************************** Function for each line: ***************************  */

/*----------------------------------------------------------------------------*/
/* functiong to simplify use of all other functions and is used as the main function to encode line of code */
bool encode_line(codeimage** current, symbol **symbol_table, char* line, int* DC, int* IC, int data_image[], externList** extern_list);



/* *************************** Encoding Command line functions: ******************** */

/*----------------------------------------------------------------------------*/
/* This function encodes the command line.
 It takes the opcode, function code, addressing modes, and register numbers as parameters. */
bool encode_command_line(codeimage** head, symbol *symbol_table, char* line, int *IC, externList** extern_list);

/*----------------------------------------------------------------------------*/
/* This function encodes the parameters in the command line. */
void encode_data_words(codeimage* current, symbol *symbol_table, char* param_source, char *param_dest, externList** extern_list, int IC);

/*----------------------------------------------------------------------------*/
/*a function to fill word for the encoded IC word*/
void load_first_word_to_code_image(codeimage* current, unsigned ARE, unsigned funct, unsigned register_dest, unsigned addressing_dest, unsigned register_source, unsigned addressing_source, unsigned opcode);

/*----------------------------------------------------------------------------*/
/*a function to handle and fill encoding for lables or parameters of immediate addressing type*/
void load_data_word_to_code_image(codeimage* current, unsigned ARE, unsigned data);



/* *************************** Encoding instruction lines functions : **************** */

/*----------------------------------------------------------------------------*/

void encode_instruction_data(char *param_line, int data_image[], int *DC);

/*----------------------------------------------------------------------------*/

void encode_instruction_string(char *param_line, int data_image[], int *DC);


#endif /* ENCODING_SERVICE_H */


