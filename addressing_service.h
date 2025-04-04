#ifndef ADDRESSING_SERVICE_H
#define ADDRESSING_SERVICE_H

#include "enable_bool.h"
#include "assembler_config_data.h"
#include "technical_functions.h"

/*data structure for the different 4 addressing method in the assembly 
language*/
typedef enum {immediate, direct, relative, direct_register} addressing_types;

typedef enum {NONE, DENY_ONLY_2, ALLOW_ONLY_1, ALLOW_1_AND_2, ALLOW_1_AND_3} addressing_options;

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
bool mapper_addressing_types_and_options(addressing_options addressing_option, addressing_types addressing_type);


/*----------------------------------------------------------------------------*/
/*check the addressing for each addressing type
assuming src_or_dst is correct and index is correct*/
bool validate_addressing_to_received_opcode_param(int index, char* word, int src_or_dst, int cline);

/* 
********************* Functions - Recognizes the addressing type of a string: *********************
*/

/*----------------------------------------------------------------------------*/
/*we assume the parameter we get is with no spaces
This function checks the addressing type of a string and returns the corresponding */
addressing_types identify_addressing_type(char *str);

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