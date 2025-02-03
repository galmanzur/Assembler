/* Declarations for functions, types, and constants */
#ifndef MACHINE_CODE_REPO_H
#define MACHINE_CODE_REPO_H

#include "lines_parser.h"
#include "symbol_service.h"

#define WORD_SIZE 24 /* word size in bits */
#define MAX_WORDS 3 /* maximum wors in memory for each line in the .am file */

/* Define a struct for a errors list */
typedef struct {
    char **words;
    int num_words;
    int word_capacity;
} code_table;

/// @brief Write the memory table to a file
/// @param errors_list 
/// @param filename 
/// @param word_list 
/// @param line_count 
/// @param max 
void write_code_table(error_table *errors_list,char *filename, code_table *word_list, char **line_count, int max);

void add_to_code_table(code_table *ob_list, code_table *word_list);

void init_code_table(code_table *ob_list);

void add_to_code_table(code_table *ob_list, code_table *word_list);

void print_code_table(code_table *ob_list,char *name);

void free_memory_table(code_table *word_list);

#endif /* MACHINE_CODE_REPO_H */