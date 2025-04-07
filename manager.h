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
#define MAX_LABEL 30 /*defining max label size*/
#define MAX_LINE 81 /*max line in code is 80 + line end '\0' == 81*/

#define NUM_OPCODES 16
#define NUM_REGISTERS 8
#define NUM_INSTRUCTIONS 4

typedef enum {DATA, STRING, ENTRY, EXTERN} instructions_types;

/* The 8 registers r0-r7 of the CPU */
extern const char *registers[NUM_REGISTERS];

/* Array of valid instructions for data types of the assembler. "
 * These instructions are used to define data/string and entry/extern. */
extern const char *instructions[NUM_INSTRUCTIONS];

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
extern const opcode opcodes[NUM_OPCODES];

#endif /* MANAGER_H */


