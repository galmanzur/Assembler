#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* This header file contains the configuration data for the assembler.
 * It includes definitions for opcodes, registers, and other constants used in the assembler.
 * The file also includes function prototypes and external variable declarations. */

/*----------------------------------------------------------------------------*/
#define MAX_LENGTH_LABEL 30 /*defining max label size*/
#define MAX_LENGTH_LINE 81 /*max line in code is 80 + line end '\0' == 81*/

#define NUMBER_OF_OPCODES 16
#define NUMBER_OF_REGISTERS 8
#define NUMBER_OF_DIRECTIVES 4

typedef enum {DIRECTIVE_DATA = 0, DIRECTIVE_STRING = 1, DIRECTIVE_ENTRY = 2, DIRECTIVE_EXTERN = 3} directive_type;

/* This list contains the names of the directives used in the assembler. */
extern const char *directives_str[NUMBER_OF_DIRECTIVES];

/* The 8 registers r0-r7 of the CPU */
extern const char *registers[NUMBER_OF_REGISTERS];

/* The opcodes of the assembler. Each opcode has a name, an opcode number,
 * a function code, and the number of parameters it takes. */
typedef struct
{
	char* name;
	int opcode_num;
	int funct;
	int params_num;
} opcode;

/* The opcodes array contains all the opcodes used in the assembler. */
extern const opcode opcodes[NUMBER_OF_OPCODES];

#endif /* MANAGER_H */


