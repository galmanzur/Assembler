#ifndef ASSEMBLER_DATA_H
#define ASSEMBLER_DATA_H

/*----------------------------------------------------------------------------*/
#define MAX_LINE 81 /*max line in code is 80 + line end '\0' == 81*/
#define MAX_FILENAME 255 /*the maximum chars in file name in NTFS*/
#define MAX_LABEL 30 /*defining max label size*/
/*----------------------------------------------------------------------------*/

/*defines thew amount of useble memory for the assembly code which is 
256 total words minus 100 used for the OS, etc...*/
#define USABLE_MEMORY_SIZE 156


/*----------------------------------------------------------------------------*/
/*data structues for the E,R,A bits that represents encoding type*/
typedef enum {absolute, external, relocatable} encoding_type;

/*----------------------------------------------------------------------------*/
/*data structure for the different 4 addressing method in the assembly 
language*/
typedef enum {immediate, direct, param_jump, direct_register} addressing;


/*----------------------------------------------------------------------------*/
/*a structure for the encoded IC line in code image*/
typedef struct 
{
	unsigned int ARE: 2; 
	unsigned int dest: 2;
	unsigned int source: 2;
	unsigned int opcode: 4;
	unsigned int param2: 2;
	unsigned int param1: 2;
} encoded_IC;

/*----------------------------------------------------------------------------*/
/*a struct for label or immediate encoding*/
typedef struct 
{
	unsigned int ARE: 2; 
	unsigned int address: 12;
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