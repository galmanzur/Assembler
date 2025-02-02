#include "pre_assembler.h"
#include "lines_parser.h"
#include "main_assembler.h"

/// @brief Validate if the given filename has a valid .as extension
/// @param filename 
/// @return 
int validate_arg_file(char *filename); 


 /// @brief Initializes the filenames for the output files (ob_file, ext_file, ent_file)
 /// @param argv 
 /// @param ob_file 
 /// @param ext_file 
 /// @param ent_file 
 /// @param ext 
 void create_files(char *argv, char **ob_file, char **ext_file, char **ent_file, char *ext);


/// @brief Main function that runs the assembler on each file
// 1. call Pre-assembler and create file.am
// 2. if there errors then stop and print them
// 3. call first pass and create file.ob
// -- if there errors then stop and print them
// * call second pass and create file.ext and file.ent
// -- if there errors then stop and print them
// * call free all memory allocations
/// @param argv 
/// @param table 
/// @param errors_list 
/// @param line 
/// @param token 
/// @param command_table 
/// @param am_file_name 
/// @param as_file_original 
/// @param registers 
/// @param directives 
/// @param line_copy 
/// @param ob_file 
/// @param ext_file 
/// @param ent_file 
/// @param fp 
void call_assembler(char *argv, symbol_table *table, error_table *errors_list, char *line, char *token, command_field *command_table, char *am_file_name, char **as_file_original, char **registers, char **directives, char *line_copy, char *ob_file, char *ext_file, char *ent_file, FILE **fp);

/// @brief Flushes resources by freeing memory and clearing error lists
/// @param table 
/// @param errors_list 
/// @param line 
/// @param token 
/// @param am_file_name 
/// @param fp 
void free_resources(symbol_table *table, error_table *errors_list, char *line, char *token, char *am_file,FILE **fp);

/// @brief Frees the memory allocated for the registers and directives arrays
/// @param registers an array of strings representing the names of the registers
/// @param directives an array of strings representing the names of the directives
void free_main(char **registers, char **directives);