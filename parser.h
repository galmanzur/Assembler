/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                             Parser👁️‍🗨️
This file contains functions for parsing assembly code.
It includes functions to identify and validare labels, opcodes, addressing types and more.
It is used to validate the syntax of assembly code and ensure that it follows the correct format.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

 #ifndef PARSER_H
#define PARSER_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#define ASCII_MAX 127
#define ASCII_MIN 0

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "enable_bool.h"
#include "print_to_console_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a character is ascii character.
* It takes an integer as a parameter and returns true if the character is ASCII, false otherwise. */
bool is_ascii(int number);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a number is a legal number.
    Legal number is one of the following: X, +X, -X. (In order the instructions. )
 *   It takes a string as a parameter and returns true if the number is legal, false otherwise. */
bool is_legal_number(char *number_str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is opcode.
* It takes a string as a parameter and returns the index of the opcode in the opcode list if it is valid, -1 otherwise. */
int get_opcode(char *opcode_str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a directive.
* It takes a string as a parameter and returns the index of the directive in the directive list if it is valid, -1 otherwise. */
directive_type get_directive_in_line(char *directive_str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a command.
 * It takes a string as a parameter and returns true if the string is a command, false otherwise. */
bool is_command(char *command_str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a word is a safe word.
* It takes a string as a parameter and returns true if the word is a safe (already exists in assmembler syntex) word, false otherwise. */
bool is_safe_word(char *word);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a line is blank or a comment.
* It takes a string as a parameter and returns true if the line is blank or a comment, false otherwise. */
bool is_blank_or_comment(char* line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a label ends with a colon.
 It takes a string as a parameter and returns true if the label ends with a colon, false otherwise. */
bool is_label_end_with_colon(char *label);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a register in the assembler.
 It takes a string as a parameter and returns true if the string is a register, false otherwise. */
bool is_register_in_assembler(char *register_str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a label.
 It takes a string and the current line number as parameters and returns true if the string is a label, false otherwise. */
bool is_label(char *label_str, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a line is valid based on the format: opcode param1 , param 2
* It takes a string and the current line number as parameters.*/
bool is_legal_commas_in_instruction(char* line, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if there is a label before .entry or .extern and prints warning if there is. */
void do_warning_if_entry_or_extern_after_label(char* line, int current_line);

#endif /* PARSER_H */