#ifndef ASSEMBLER_DATA_H
#define ASSEMBLER_DATA_H

/*----------------------------------------------------------------------------*/
#define MAX_LINE 81 /*max line in code is 80 + line end '\0' == 81*/
#define MAX_LABEL 30 /*defining max label size*/

/*----------------------------------------------------------------------------*/

/*defines thew amount of useble memory for the assembly code which is 
256 total words minus 100 used for the OS, etc...*/
#define USABLE_MEMORY_SIZE 156

/*----------------------------------------------------------------------------*/
/*data structues for the E,R,A bits that represents encoding type*/
typedef enum {absolute, external, relocatable} encoding_type;

/*----------------------------------------------------------------------------*/

#define SRC 0
#define DST 1

/*----------------------------------------------------------------------------*/
/*a structure for the encoded IC line in code image.
 The encoded instruction is a binary representation of the instruction line in the assembly code.
 It contains fields for the opcode, function code, addressing modes, and register numbers.
 The fields are defined using bit fields to optimize memory usage.
size- 24 bits
*/
typedef struct 
{
	unsigned int ARE: 3; 
	unsigned int funct: 5; /* Represents the function code of the instruction. */
	unsigned int dest: 2; /* Represents the addressing mode of the destination operand */
	unsigned int source: 2; /* Represents the addressing mode of the source operand */
	unsigned int opcode: 6; /* Encodes the operation code (instruction type). */
	unsigned int register_dest: 3; /* Encodes the register number or value associated with the second operand (destination).n*/
	unsigned int register_source: 3; /* Encodes the register number or value associated with the first operand (source)*/
} encoded_IC;

/*----------------------------------------------------------------------------*/
/*a struct for label or immediate encoding

ARE - 
00 – Absolute (A): Immediate values or internal constants

01 – Relocatable (R): Refers to a symbol defined in the same program

10 – External (E): Refers to a symbol defined outside the current file

Bit size: 2 bits

Address - Holds the actual value or address.

If it's an immediate operand, this is the immediate value itself.

If it's a label, this is the address of the label in memory.

Bit size: 12 bits

*/
typedef struct 
{
	unsigned int ARE: 3; 
	unsigned int address: 22;
} label_or_immediate;

/*----------------------------------------------------------------------------*/
/*a struct for register word encoding*/
typedef struct
{
	unsigned int ARE: 2;
	unsigned int dest: 6;
	unsigned int source: 6;
} register_word;

/*----------------------------------------------------------------------------*/
typedef struct codeimage
{
	struct codeimage *next;
	union
	{
		unsigned int bit;
		encoded_IC first;
		label_or_immediate address;
		register_word reg;
	} encoded_instruction[4]; /*because max of 4 words in instruction see guide*/
	int L;
} codeimage;

/*----------------------------------------------------------------------------*/
/*a struct used for the .ext file to store IC lines where external lable were 
used*/
typedef struct externList
{
	struct externList *next;
	int address;
	char name[MAX_LABEL];

} externList;
/*----------------------------------------------------------------------------*/

#endif /* ASSEMBLER_DATA_H */