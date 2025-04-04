#ifndef ENCODING_DATA_H
#define ENCODING_DATA_H

#include "assembler_config_data.h"
#include "enable_bool.h"
#include "addressing_service.h"
#include "process_data.h"
#include "symbol_repo.h"
#include "parser.h"
#include "file_service.h"

/* Usable memory of project's PC: 2 ^ 21 - 100. */
#define USABLE_MEMORY_SIZE 2097052

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
/*a struct for label or immediate encoding*/
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

#endif /* ENCODING_DATA */