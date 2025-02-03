#ifndef CODE_PROCESSOR_H
#define CODE_PROCESSOR_H

#include "lines_parser.h"
#include "symbol_service.h"
#include "error_repo.h"
#include "file_service.h"
#include "machine_code_repo.h" 

/// @brief Convert an integer or character string to a binary string representation
/// @param number_str A string representing an integer or character
/// @param num_bits number of bits to represent the binary string
/// @param binary_string A pointer to a string to store the binary representation
void convert_to_binary(char *number_str, int num_bits, char **binary_string);

/// @brief Validate that a string consists of only binary digits (0 and 1)
/// @param string A string to validate
/// @param return_str A pointer to a string to store the validated binary string
void validate_bits(char *string, char **return_str);

/// @brief Get the binary code for a given token
/// @param token A string representing the token to get the binary code for
/// @param registers A pointer to an array of register names
/// @return A string representing the binary code for the token
char *get_binary_code(char *token, char ***registers);

/// @brief 
/// @param word_list 
/// @return 
int get_num_words(memory_table *word_list);

char *get_word(memory_table *word_list, int i);

char *get_first_word(symbol_table *table, command_field *command_table, char ***registers, char *command, char *first_op, char *second_op);


void add_word(memory_table *word_list,char *word,int x);

void evaluate_command(symbol_table *table, memory_table *word_list, command_field *command_table,error_table *errors_list, char **am_file, char **ext_file, char ***registers,char ***directives, char *line, int line_number, int first_assemble, char **line_copy);

void first_assemble(memory_table *word_list, symbol_table *table,error_table *errors_list, char **line, char **token, command_field *command_table, char **am_file,char **ext_file, FILE **fp,  char ***registers, char ***directives, char **line_copy);

void second_assemble(memory_table *data_binary, memory_table *instruction_binary, memory_table *word_list, symbol_table *table,error_table *errors_list, char **line, char **token, command_field *command_table, char **am_file, char **ob_file, char **ent_file, char **ext_file, FILE **fp,  char ***registers, char ***directives, char **line_copy);


#endif /* CODE_PROCESSOR_H */
