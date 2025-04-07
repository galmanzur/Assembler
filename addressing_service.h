/* 
                                    Addressing Service 🚗🚚✈️
 * This file contains the function definitions for validating addressing types in assembler.
 * It includes functions to validate immediate, direct, relative, and direct register addressing types.
 * The file also contains a function to identify the addressing type of a string and a function to map addressing options to addressing types.
 * The functions are used in the first pass of the assembler to ensure that the addressing types are valid according to the opcode table.
 */

#ifndef ADDRESSING_SERVICE_H
#define ADDRESSING_SERVICE_H

#include "enable_bool.h"
#include "manager.h"
#include "technical_functions.h"
#include "print_to_console_service.h"
#include "parser.h"

/* ----------------------------------------------------------------------------*/

/* This enum defines the different addressing types that can be used in the assembler. */ 
typedef enum {ADDRESSING_IMMEDITAE, ADDRESSING_DIRECT, ADDRESSING_RELATIVE, ADDRESSING_DIRECT_REGISTER} addressing_type_of_opcode;

/* This enum defines the different addressing options that can be used with opcodes - which addressing types are allowed for each opcode. */
typedef enum {NONE_ADDRESSING_ALLOW, DENY_ONLY_ADDRESSING_2, ALLOW_ONLY_ADDRESSING_1, ALLOW_ADDRESSING_1_AND_2, ALLOW_ADDRESSING_1_AND_3} addressing_option_of_opcode;

/* This struct represents an opcode in the assembler.
 It contains the opcode number, function code, and the number of parameters required for the opcode. */
typedef struct opcode_and_addressing_for_each_param
{
    const opcode *opcode;
	int source; 
    int destination;
} opcode_and_addressing_for_each_param;

/* Needs to be initialized the with the addressing types for each opcode (in C file). */ 
extern const opcode_and_addressing_for_each_param opcodes_table[];

/*----------------------------------------------------------------------------*/
/*getting str and cline and checks immediate adressing validation
if valid returns true, else return false + indicative error message*/
bool validate_immediate(char *str, int cline);

/*----------------------------------------------------------------------------*/
/*getting str and cline and checks direcr register adressing validation
if valid returns true, else return false + indicative error message*/
bool validate_direct_register(char *str, int cline);

/*----------------------------------------------------------------------------*/
/*function to get str and cline to check if all addressing is valid
except for addressing type number 2*/
bool validate_except_paramjump(char *str, int cline);

/*----------------------------------------------------------------------------*/
/*assuming all spaces and ',' are validating param_jump addressing type
with cline for indicative error*/
bool validate_relative(char *line, int cline);

/*----------------------------------------------------------------------------*/
/*checks if addressing is written correctly*/
bool validate_relevantive_addressing(char *str, int cline, char *line);

/*----------------------------------------------------------------------------*/
/*function with switch case getting addressing status and 
addressing type and handel accordingly - will be used in validate addressing
type*/
bool mapper_addressing_types_and_options(addressing_option_of_opcode addressing_option, addressing_type_of_opcode addressing_type);


/*----------------------------------------------------------------------------*/
/*check the addressing for each addressing type
assuming src_or_dst is correct and index is correct*/
bool validate_addressing_to_received_opcode_param(int index, char* word, int src_or_dst, int cline);


/********************** Functions - Recognizes the addressing type of a string: **********************/

/*----------------------------------------------------------------------------*/
/*we assume the parameter we get is with no spaces
This function checks the addressing type of a string and returns the corresponding */
addressing_type_of_opcode identify_addressing_type(char *str);

/*----------------------------------------------------------------------------*/
/*checking if str is of immediate addressing type */
bool is_immediate_addressing(char *str);

/*----------------------------------------------------------------------------*/
/*check if str is of type param_jump addressing*/
bool is_relative_addressing(char *str);

/*----------------------------------------------------------------------------*/
/*check if str is of type direct_register addressing return true or false depends*/
bool is_direct_register_addressing(char *str);

#endif /* ADDRESSING_SERVICE_H */