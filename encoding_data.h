#ifndef ENCODING_DATA_H
#define ENCODING_DATA_H
#include "manager.h"

/* Usable memory of project's PC: 2 ^ 21 - 100. */
#define ASSEMBLER_MEMORY_SIZE 2097052

#define SIZE_OF_WORD 24 /* size of a word in bits */

/* max label size in assembler language */
#define MAX_WORDS_FOR_INSTRUCTION 3 

/*----------------------------------------------------------------------------*/
/*data structues for the E,R,A bits that represents encoding type
 * 4 for the third bit (A) of the ARE field in the instruction word.
 * 2 for the second bit(R) of the ARE field in the instruction word.
 * 1 for the first bit(E) of the ARE field in the instruction word. */
typedef enum {absolute = 4, relocatable = 2, external = 1} encoding_type;
/*----------------------------------------------------------------------------*/

#define SRC 0
#define DST 1

 /* Represents the first word of a machine instruction in the assembler.
 * The first word contains the fields:
 *   ARE: (3 bits)  Indicates the type of reference: Absolute, External, Relocatable.
 *   funct: (5 bits)  Optional function code used by some instructions.
 *   register_dest: (3 bits)  Destination register number (r0-r7).
 *   addressing_dest: (2 bits)  Addressing mode of the destination operand.
 *   register_source: (3 bits)  Source register number (r0-r7).
 *   addressing_source: (2 bits)  Addressing mode of the source operand.
 *   opcode: (6 bits)  Main operation code (up to 16 instructions).
 */
typedef struct 
{
	unsigned int ARE: 3; 
	unsigned int funct: 5; /* Represents the function code of the instruction. */
	unsigned int register_dest: 3; /* Encodes the register number or value associated with the second operand (destination).n*/
	unsigned int addressing_dest: 2; /* Represents the addressing mode of the destination operand */
	unsigned int register_source: 3; /* Encodes the register number or value associated with the first operand (source)*/
	unsigned int addressing_source: 2; /* Represents the addressing mode of the source operand */
	unsigned int opcode: 6; /* Encodes the operation code (instruction type). */
} structure_of_opcode_word;


/* Represents an additional word in the instruction (beyond the first),
* Used to encode:
* - Immediate values (#number) - immediate addressing
* - Addresses for labels - direct addressing
* - how many words to jump to - relative addressing
----------------------------------------------------------------------------*/
typedef struct 
{
	unsigned int ARE: 3; 
	unsigned int data: 21;
} structure_of_additional_data_word;


 /* Represents a node in the linked list that holds the encoded instruction words. * 
 * Fields:
 * next: Pointer to the next instruction node.
 * encoded_instruction[]: Union holding either the first opcode word or 
 * additional data words, each occupying 24 bits total.
 * Number of words used in this instruction (1-3). */
typedef struct codeimage
{
	struct codeimage *next;
	union
	{
		unsigned int bit;
		structure_of_opcode_word first;
		structure_of_additional_data_word data_word;
	} encoded_instruction[MAX_WORDS_FOR_INSTRUCTION]; 
	int number_of_words;
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