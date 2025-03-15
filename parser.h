#ifndef PARSER_H
#define PARSER_H
#include "manager.h"
#include "assembler_data.h"
#include "enable_bool.h"

/*----------------------------------------------------------------------------*/
/*checking if character is in valid ascii table range from 0 to 127
getting a char c, return true if ASCII false if not*/
bool is_ascii(int c);

/*----------------------------------------------------------------------------*/
/*function to check if number is a whole number gets a str of number and cline
for error handling*/
bool is_whole_number(char *str);

/*----------------------------------------------------------------------------*/
/*checking if word is opcodes return index in list if it is else return -1*/
int is_opcode(char *word);

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
bool blank_comment_line(char* line);

/*----------------------------------------------------------------------------*/
/*checking if label is ended in : if it is return true else use cline for indicative 
error*/
bool check_label_colon(char *label);

/*----------------------------------------------------------------------------*/
/*checking if str is of immediate addressing type */
bool immediate_addressing_check(char *str);

/*----------------------------------------------------------------------------*/
/*check if str is of type param_jump addressing*/
bool param_jump_check(char *str);

/*----------------------------------------------------------------------------*/
/*check if str is of type direct_register addressing return true or false depends*/
bool direct_register_check(char *str);

/*----------------------------------------------------------------------------*/
/*we assume the parameter we get is with no spaces
get addressing type of str using above functions*/
addressing check_addressing_type(char *str);

/*----------------------------------------------------------------------------*/
/*assuming opcode correct get line and check if starts with comma*/
bool start_with_coma(char *line, int cline);

/*----------------------------------------------------------------------------*/
/*assuming opcode correct get line and check if ends with comma*/
bool end_with_coma(char *line, int cline);

/*----------------------------------------------------------------------------*/
/*function to count number of commas in line*/
int mutiple_comma(char* line);

/*----------------------------------------------------------------------------*/
/*function to check if word is register*/
bool is_register(char *word);

#endif /* PARSER_H */