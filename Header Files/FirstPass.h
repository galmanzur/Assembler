#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <error_service.h>
#include "symbol_service.h"
#include "lines_parser.h"

/* Declarations for functions, types, and constants */
#define MAX_LABEL_SIZE 31 /* MAX characters in label is 31 chars*/

/// @brief Initializes the parser by setting the file extensions and initializing the error list.
/// @param as_file 
/// @param am_file 
/// @param as_file_original 
/// @return 
int init_parser(char *as_file, char **am_file, char **as_file_original);

/// @brief Parses the entire input file line by line, and calls `parse_line()` for each line.
/// @param symbols - pointer to the symbol table
/// @param errors_list - pointer to the error table
/// @param line - pointer to the current line in the input file
/// @param token - pointer to the current token in the current line
/// @param command_table - pointer to the command table
/// @param am_file - pointer to the .am output file
/// @param as_file_original - pointer to the original .as input file
/// @param fp - pointer to the input file stream
/// @param registers -  array of the register names
/// @param directives - array of the directive names
/// @param line_copy - pointer to a copy of the current line
/// @return 
int parse_file(symbol_table *symbols,error_table *errors_list, char **line, char **token, command_field *command_table, char **am_file, char **as_file_original, FILE **fp,  char ***registers, char ***directives, char **line_copy);

/// @brief  * Parses a single line from the input file.
/// @param symbols -  pointer to the symbol table
/// @param errors_list - pointer to the error table
/// @param token - pointer to the current token in the line
/// @param command_table - pointer to the command table
/// @param row_counter - current row number in the input file
/// @param macro_flag - flag indicating whether a macro is being defined or not
/// @param declaration_flag - flag indicating whether a declaration is being made or not
/// @param am_file - pointer to the .am output file
/// @param as_file_original - pointer to the original .as input file
/// @param registers - array of the register names
/// @param directives - array of the directive names
/// @return returns 1 if successful, 0 otherwise
int parse_line(symbol_table *symbols,error_table *errors_list, char **token, command_field *command_table, int row_counter, int *macro_flag, int *declaration_flag, char **am_file,char **as_file_original, char ***registers, char ***directives);


/// @brief Check if a given string is a valid string. a valid string starts with " and ends with " without ; in the middle
/// @param str The string to check
/// @return A pointer to the first character of the string if it is valid, NULL otherwise
char * is_valid_string(char *str);

/// @brief Returns the index of the last non-whitespace character in a string, starting from the end of the string and iterating backwards.
/// @param string 
/// @return 
int last_non_whitespace_index(char *string);

/// @brief Returns the number of arguments in a string delimited by commas, spaces, or tabs.
/// @param str The input string to count the number of arguments.
/// @return The number of arguments in the string.
int how_many_args(char *str);

/// @brief Determines if a given string represents a valid data declaration.
/// A valid data declaration is a string that is not enclosed in double quotes, and contains no commas or a comma followed by another comma.
/// @param str The input string to check if it represents a valid data declaration.
/// @return Returns 1 if the string is a valid data declaration, 0 otherwise
int is_valid_data(char *str);

/// @brief This function determines whether a given string is a valid integer number.
/// @param str The input string to check if it is a valid number.
/// @return Returns 1 if the string is a valid number, 0 otherwise
int is_valid_number(char *str);


#endif /* FIRST_PASS_H */
