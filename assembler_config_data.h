#ifndef ASSEMBLER_CONFIG_DATA_H
#define ASSEMBLER_CONFIG_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*this file contains the list of instruction, registers and opcodes uses
in our tasks assembly and compouter*/
/*definition of numbers of opcodes, registers, instruction for later*/
#define NUM_OPCODES 16
#define NUM_REGISTERS 8
#define NUM_INSTRUCTIONS 4

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

#endif /* ASSEMBLER_CONFIG_DATA */


