/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                                 ** Addressing Service 🚗🚚✈️ **
 * This file contains the functions definitions for validating addressing types in assembler.
 * It includes functions to validate immediate, direct, relative, and direct register addressing types.
 * The file also contains a function to identify the addressing type of a string and a function to map addressing options to addressing types.
 * The functions are used in the first pass of the assembler to ensure that the addressing types are valid according to the opcode table.
 * The functions are also used in the second pass of the assembler to encode the instructions correctly.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef ADDRESSING_SERVICE_H
#define ADDRESSING_SERVICE_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "enable_bool.h"
#include "manager.h"
#include "technical_functions.h"
#include "print_to_console_service.h"
#include "parser.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This enum defines the different addressing types that can be used in the assembler. */ 
typedef enum {ADDRESSING_IMMEDITAE, ADDRESSING_DIRECT, ADDRESSING_RELATIVE, ADDRESSING_DIRECT_REGISTER} addressing_type_of_opcode;

/* This enum defines the different addressing options that can be used with opcodes - which addressing types are allowed for each opcode.
None Addressing Allow - no addressing types are allowed for this opcode.
Deny Only Addressing 2 - only addressing type 2 is not allowed for this opcode.
Allow Only Addressing 1 - only addressing type 1 is allowed for this opcode.
Allow Addressing 1 and 2 - both addressing types 1 and 2 are allowed for this opcode.
Allow Addressing 1 and 3 - both addressing types 1 and 3 are allowed for this opcode. */
typedef enum {NONE_ADDRESSING_ALLOW, DENY_ONLY_ADDRESSING_2, ALLOW_ONLY_ADDRESSING_1, ALLOW_ADDRESSING_1_AND_2, ALLOW_ADDRESSING_1_AND_3} addressing_option_of_opcode;

/* This struct represents an opcode in the assembler.
 It contains the opcode number, function code, and the number of parameters required for the opcode. */
typedef struct opcode_and_addressing_for_each_param
{
    const opcode *opcode;
	int source; 
    int destination;
} opcode_and_addressing_for_each_param;

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This array maps opcodes to their addressing types for each parameter.
 It is used to validate the addressing types in the assembler. 
Needs to be initialized the with the addressing types for each opcode (in C file). */ 
extern const opcode_and_addressing_for_each_param opcodes_table[];

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function gets str and current_line and checks immediate adressing validation
if valid returns true, else return false.*/
bool validate_immediate(char *str, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function gets str and current_line and checks direct register addressing validation 
If valid returns true, else returns false */
bool validate_direct_register(char *str, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function gets str and current_line and checks relative adressing validation
if valid returns true, else return false.*/
bool validate_relative(char *line, int current_line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/** This function checks if the addressing type is valid for the given opcode.
 * It returns true if the addressing type is valid, false otherwise.
 * It uses the mapper_addressing_types_and_options function to check the addressing type against the allowed options for this opcode.
 */
bool validate_addressing_of_opcode(char *opcode_str, int current_line, char *line);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function mapps addressing types to addressing options for a given opcode.
 * It checks if the addressing type is valid for the given opcode parameter (source or destination).
 * It returns true if the addressing type is valid, false otherwise.
 */
bool mapper_addressing_types_and_options(addressing_option_of_opcode addressing_option, addressing_type_of_opcode addressing_type);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the addressing type is valid for the given opcode parameter (source or destination).
 * It returns true if the addressing type is valid, false otherwise.
 * It uses the mapper_addressing_types_and_options function to check the addressing type against the allowed options for this opcode.
 */
bool validate_addressing_to_received_opcode_param(int index, char* word, int is_source_or_dest, int current_line);

/*---------------------------------------------Identify Functions 👀----------------------------------------------                                      */

/* This function identifies the addressing type of a given string.
 * It takes a string as input and returns the corresponding addressing type.
 * It uses the is_immediate_addressing, is_relative_addressing, and is_direct_register_addressing functions to identify the addressing type.
 */
addressing_type_of_opcode identify_addressing_type(char *str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the string is of type immediate addressing.
 * It returns true if the string is of type immediate addressing, false otherwise. */
bool is_immediate_addressing(char *str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the string is of type relative addressing.
 * It returns true if the string is of type relative addressing, false otherwise. */
bool is_relative_addressing(char *str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the string is of type direct register addressing.
 * It returns true if the string is of type direct register addressing, false otherwise. */
bool is_direct_register_addressing(char *str);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* ADDRESSING_SERVICE_H */