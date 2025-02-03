 
 #ifndef ERROR_REPO_H
#define ERROR_REPO_H

#include "lines_parser.h"
#include "symbol_service.h"
#include <unistd.h>
#include <string.h>

 /* Declarations for functions, types, and constants */
 
/// @brief holds the error message and the line number and file of the error
typedef struct 
{
	char *error_file;
	int error_line;
    char *error_str;

} error;

/// @brief holds all the errors in the program
typedef struct {
    error **errors;
    int num_errors;
    int error_capacity;
} error_table;

/// @brief 
/// @param errors_list 
/// @return 
int init_error_list(error_table *errors_list);

/// @brief Adds an error to the errors list.
/// @param errors_list 
/// @param error_file 
/// @param error_line 
/// @param error_str 
void add_error(error_table *errors_list, char *error_file, int error_line, char *error_str);


/// @brief Print all errors in the error table.
/// @param errors_list - A pointer to the error_table struct containing the errors to print.
void print_errors(error_table *errors_list);

/// @brief Free all memory allocated to the error table and its contents.
/// @param errors_list - A pointer to the error_table struct to free.
void free_error_list(error_table *errors_list);

/// @brief Gets the number of errors in the error table.
/// @param errors_list - A pointer to the error_table struct to get the number of errors from.
/// @return returns the number of errors in the error table.
int get_num_errors(error_table *errors_list);


/// @brief Gets the error at the given index in the error table.
// /*error guide*/
// enum error_codes {
//     LABEL_ENTRY_EXTERN = 2,
//     LABEL_DEFINED_ENTRY,
//     LABEL_NOT_DEFINED,
//     LABEL_NOT_FOUND,
//     LABEL_ALREADY_EXISTS,
//     INVALID_LABEL_NAME,
//     INVALID_LABEL_LENGTH,
//     INVALID_LABEL_NULL,
//     INVALID_LABEL_RESERVED,
//     INVALID_LABEL_FIRST,
//     INVALID_STRING,
//     INVALID_STRING_NULL,
//     INVALID_DATA,
//     INVALID_DATA_SYNTAX,
//     INVALID_COMMAND,
//     INVALID_MISSING_OPERAND,
//     INVALID_EXTRA_OPERAND,
//     INVALID_OPERAND_DEST,
//     INVALID_OPERAND_SRC,
//     INVALID_MACRO_NAME,
//     INVALID_MACRO_NULL,
//     INVALID_MACRO_EXIST,
//     INVALID_MACRO_SYNATX,
//     INVALID_LINE_LENGTH,
//     INVALID_RELATIVE_LABEL,
//     INVALID_RELATIVE,
//     INVALID_OPERAND
// };

// /*
//     * prints the error messages
//     * @param error error code
//     * @param line_number line number of error
//     * @param line line of error
//     * @param token the cause of the error
// */
// void display_error(int error);




// #endif /* ERROR_REPO_H */
