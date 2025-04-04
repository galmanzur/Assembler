#ifndef PARSER_H
#define PARSER_H

#include "symbol_repo.h"
#include "assembler_config_data.h"
#include "enable_bool.h"

/*----------------------------------------------------------------------------*/
#define MAX_LABEL 30 /*defining max label size*/
#define MAX_LINE 81 /*max line in code is 80 + line end '\0' == 81*/

/*----------------------------------------------------------------------------*/
/*checking if character is in valid ascii table range from 0 to 127
getting a char c, return true if ASCII false if not*/
bool is_ascii(int c);

/*----------------------------------------------------------------------------*/
/*function to check if number is a whole number gets a str of number and cline
for error handling*/
bool is_legal_number(char *str);

/*----------------------------------------------------------------------------*/
/*checking if word is opcodes return index in list if it is else return -1*/
int get_opcode(char *word);

/*----------------------------------------------------------------------------*/
/*checking if word is insruction return index in list if it is else return -1*/
int is_data(char *word);

/*----------------------------------------------------------------------------*/
/*chekcing if word is opcode or instruction*/
bool is_command(char *word);

/*----------------------------------------------------------------------------*/
/*function to check if the word is a safe word if it is return true
else if name is saved word in assembly language return false*/
bool is_safe_word(char *word);

/*----------------------------------------------------------------------------*/
/*function to check if line is blank or comment line*/
bool is_blank_or_comment(char* line);

/*----------------------------------------------------------------------------*/
/*checking if label is ended in : if it is return true else use cline for indicative 
error*/
bool is_label_end_with_colon(char *label);

/*----------------------------------------------------------------------------*/
/*assuming opcode correct get line and check if starts with comma*/
bool is_start_with_coma(char *line, int cline);

/*----------------------------------------------------------------------------*/
/*assuming opcode correct get line and check if ends with comma*/
bool is_end_with_coma(char *line, int cline);

/*----------------------------------------------------------------------------*/
/*function to count number of commas in line*/
int how_much_commas(char* line);

/*----------------------------------------------------------------------------*/
/*function to check if word is register*/
bool is_register_in_assembler(char *word);

/*----------------------------------------------------------------------------*/
/*checking if label is safe if it is return true else false + indicative error
message to user*/
bool is_label(char *word, int cline);

/*----------------------------------------------------------------------------*/
/* this function checks if a line of assembly code is valid
 based on the format: opcode param1 , param 2
 there can be any number of spaces between opcode, params, and comma.*/
bool valid_line_comma_spaces(char* line, int cline);

#endif /* PARSER_H */