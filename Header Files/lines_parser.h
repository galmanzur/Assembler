/*
This module is responsible for parsing the source code line by line into a linked list composed of data structures containing tokens for each "element" in the execution line.

Element – A token based on spaces and tabs.

Each token can be one of the following:

* Label declaration
*Command
*Operand (register, number, label, label with two parameters)
*Label name
*mcr
*endmcr
*Name of a previously defined macro
*Directive (e.g., .data, .string, etc.)
*/


#ifndef LINES_PARSER_H
#define LINES_PARSER_H

#include <stdio.h> /*   functions for input and output operations. */
#include <string.h> /*  functions for manipulating strings. */ 
#include <limits.h>
#include <stdlib.h> /*  functions for memory allocation and conversion of numbers. */
#include <ctype.h> /*   functions for character classification and conversion. */
                                                             

#define MAX_LINE_SIZE 80 /* maximum input line is 80 chars */
#define NUM_COMMANDS 16 /* all the commands existing in this language */
#define NUM_OF_REGISTERS 8 /* all the registers existing in this language */
#define NUM_OF_DIRECTIVES 4 /* all the directives existing in this language */

typedef struct {
    char *name;
    char *opcode;
    int group_type;
} command_field;

/// @brief  Initializes the parser by opening the input file and reading the first line. It also initializes the command table, registers, and directives. Returns 1 if successful.
/// @param filename - The name of the input file.
/// @param extension - The expected extension of the input file.
/// @param line - A pointer to the current line being read.
/// @param token - A pointer to the current token being read.
/// @param command_table - An array of command_fields representing the available commands.
/// @param fp - A pointer to the file pointer for the input file.
/// @param registers - A pointer to an array of strings representing the available registers.
/// @param directives - A pointer to an array of strings representing the available directives.
/// @param line_copy - A pointer to a copy of the current line being read.
/// @return 
int init_parser(char *filename, char *extension, char **line, char **token, command_field *command_table, FILE **fp, char ***registers, char ***directives, char **line_copy);

/// @brief Creates a new command with the given name, opcode, and group type.
/// @param name 
/// @param opcode1 
/// @param group_type1 
/// @return 
command_field create_command(char *name, char *opcode1,int group_type1);

/// @brief Resets and frees dynamically allocated variables before exiting.
/// @param fp 
/// @param registers 
/// @param directives 
void refresh_parser(FILE **fp,  char ***registers, char ***directives);

/// @brief Reads the next line from the input file and updates the line and token pointers accordingly.
/// @param line 
/// @param token 
/// @param fp 
/// @param line_copy 
void get_next_line(char **line, char **token, FILE **fp, char **line_copy);

/// @brief Determines if the current line is the last line of the input file.
/// @param line 
/// @param fp 
/// @param registers 
/// @param directives 
/// @param last_line_flag 
/// @return 0 if the line is not the last line, 1 if the line is the last line
int is_last_line(char **line,FILE **fp, char ***registers, char ***directives, int *last_line_flag);

/// @brief Determines if the given token is a label declaration.
/// @param token 
/// @return returns 1 if the token is a label declaration, 0 otherwise
int is_label_declaration(char *token);

/// @brief Determines if the given token is a command.
/// @param token 
/// @param command_table 
/// @return returns 1 if the token is a command, 0 otherwise
int is_command(char *token, command_field *command_table);

/// @brief This function checks if a given token is a register name or not.
/// @param token (char*): A string representing the token to check.
/// @param registers (char***): A pointer to an array of register names.
/// @return returns 1 if the token is a register, 0 otherwise
int is_register(char *token, char ***registers);

/// @brief This function checks if a given token is a number or not.
/// @param token 
/// @return returns 1 if the token is a number, 0 otherwise
int is_number(char *token);

/// @brief This function extracts the label from a given token. If the token ends with a colon, the function returns a new string that is a copy of the token without the colon.
/// Otherwise, it returns a pointer to the original token.
/// @param token (char*): A string representing the token to extract the label from.
/// @return 
char *get_label(char *token);


/// @brief This function checks if a given token is a comment or not.
/// @param token (char*): A string representing the token to check.
/// @return returns 1 if the token is a comment, 0 otherwise
int is_comment(char *token);

/// @brief * This function checks if a given token is a directive or not.
/// @param token (char*): A string representing the token to check.
/// @param directives (char***): A pointer to an array of directive names.
/// @return returns 1 if the token is a directive, 0 otherwise
int is_directive(char *token, char ***directives);

/// @brief This function checks if a given token is a safe word or not. A safe word is either a directive, register, command, or macro.
/// @param token (char*): A string representing the token to check.
/// @param str (char*): A string representing the original input line.
/// @param command_table (command_field*): A pointer to an array of command_field structs.
/// @param registers (char***): A pointer to an array of register names.
/// @param directives (char***): A pointer to an array of directive names.)
/// @return returns 1 if the token is a safe word, 0 otherwise
int is_safe_word(char *token, char *str, command_field *command_table, char ***registers, char ***directives);

/// @brief This function extracts the register number from a given token.
/// The token is assumed to be a valid register name (i.e., it starts with the character 'r' followed by a number).
/// The function returns a new string containing the register number.
/// @param token (char*): A string representing the register name to extract the number from.
/// @return 
char *get_register_number(char *token);

/// @brief 
/// * This function returns the group type of a given command.
/// * If the command is found in the command_table array, the function returns the corresponding group type. Otherwise, it returns -1.
/// @param token (char*): A string representing the command to get the group type for.
/// @param command_table (command_field*): A pointer to an array of command_field structs.
/// @return The group type of the command (if found), or -1 otherwise.
int get_group_type(char *token, command_field *command_table);

/// @brief This function returns the opcode of a given command.
/// If the command is found in the command_table array, the function returns the corresponding opcode. Otherwise, it returns NULL.
/// @param command (char*): A string representing the command to get the opcode for.
/// @param command_table (command_field*): A pointer to an array of command_field structs.
/// @return The opcode of the command (if found), or NULL otherwise.
char *get_command_opcode(char *command,command_field *command_table);

/// @brief  * This function converts a given string to a number.
/// The string is assumed to represent a valid number (i.e., it contains only digits and an optional leading '+' or '-').
/// The function returns the number as an integer.
/// @param str (char*): A string representing the number to convert.
/// @return The number represented by the input string.
int convert_to_number(char *str);


#endif /* LINES_PARSER_H */
