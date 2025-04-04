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

/*the assembly language opcodes array, the index of each opcode in the array 
is given by the value it gets in machine language*/


/*the 8 registers r0-r7 of the CPU placed in the imaginery computer for this 
task*/
extern const char *registers[NUM_REGISTERS];

/*array of valid instructions for data types of the assembler*/
extern const char *instructions[NUM_INSTRUCTIONS];

typedef struct
{
	char* name;
	int opcode_num;
	int funct;
	int params_num;
} opcode;

extern const opcode opcodes[NUM_OPCODES];
/*extern const char *opcodes[NUM_OPCODES];*/

#endif /* MANAGER_H */


