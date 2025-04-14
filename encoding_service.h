/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                                 Encoding Service 📜
* This file contain the functions of encoding the assembler instructions and data into Code image and Data image.
* The functions include encoding the line, command line, data words, and loading the words of the instruction into the code image.

** Notice: 📑🖼️ 
You can see in "Important Documents" --> "Drawing of Encode Words.pdf" of this project:
My drawing of the encoding of each word - The code is built according to the drawing that constitutes the requirements.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef ENCODING_SERVICE_H
#define ENCODING_SERVICE_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

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

/*->->->->->->->->->->->->->->->->->->->->->->- Main Function (For each line) ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function encodes the line and calling the other help functions, then - puts it in the code image.
 It takes the current code image node, symbol table, line, instruction counter (IC), data counter (DC), and extern list as parameters.
 It returns true if the encoding was successful, false otherwise. */
bool encode_line(codeimage** current, symbol **symbol_table, char* line, int* DC, int* IC, int data_image[], externList** extern_list, int current_line, bool is_first_pass_success);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function encodes the command line and puts it in the code image.
 It takes the head of the code image linked list, symbol table, line, instruction counter (IC), and extern list as parameters.
 It returns true if the encoding was successful, false otherwise. */
bool encode_command_line(codeimage** head, symbol *symbol_table, char* line, int *IC, externList** extern_list, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function encodes the data words (The additional words of each instruction in order the requirements) in the code image.
 It takes the current code image node, symbol table, source and destination parameters, extern list, and instruction counter as parameters. */
void encode_data_words(codeimage* current, symbol *symbol_table, char* param_source, char *param_dest, externList** extern_list, int IC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function loads the first word of the instruction into the code image.
 It takes the current code image node, ARE, funct, register numbers, addressing modes, and opcode as parameters. */
void load_first_word_to_code_image(codeimage* current, unsigned ARE, unsigned funct, unsigned register_dest, unsigned addressing_dest, unsigned register_source, unsigned addressing_source, unsigned opcode);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function loads the data word into the code image.
 It takes the current code image node, ARE, and data as parameters. */
void load_data_word_to_code_image(codeimage* current, unsigned ARE, unsigned data);

/*->->->->->->->->->->->->->->->->->->->->->-> Encoding Directive Functions >->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function encodes the instruction data (numbers) in the second pass.
 It takes the parameter line, data image array, and data counter as parameters. */
void encode_instruction_data(char *param_line, int data_image[], int *DC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function encodes the instruction string in the second pass.
 It takes the parameter line, data image array, and data counter as parameters. */
void encode_instruction_string(char *param_line, int data_image[], int *DC);

#endif /* ENCODING_SERVICE_H */


