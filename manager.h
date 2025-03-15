#ifndef MANAGER_H
#define MANAGER_H

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

typedef enum {NONE, ALLBUT0, ALLBUT2, ALLBUT02, NOTHINGBUT1} addressing_options;

/*the assembly language opcodes array, the index of each opcode in the array 
is given by the value it gets in machine language*/
extern const char *opcodes[NUM_OPCODES];

/*the 8 registers r0-r7 of the CPU placed in the imaginery computer for this 
task*/
extern const char *registers[NUM_REGISTERS];

/*array of valid instructions for data types of the assembler*/
extern const char *instructions[NUM_INSTRUCTIONS];

typedef struct opcode_param_and_addressing_table
{
	int source, destination;
} opcode_param_and_addressing_table;

extern const opcode_param_and_addressing_table opcodes_table[];

#endif /* MANAGER_H */


