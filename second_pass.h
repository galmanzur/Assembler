#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "file_service.h"
#include "symbol_repo.h"
#include "assembler_config_data.h"
#include "enable_bool.h"
#include "addressing_service.h"
#include "parser.h"
#include "encoding_data.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/*function to hanlde th second pass in this two pass assembler*/
bool second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list);
   
/*----------------------------------------------------------------------------*/
/*function to destroy the code image after we are done using it*/
void destroy_codeimage(codeimage* head);

/*----------------------------------------------------------------------------*/
/*function to desytoy list of the extern labels and their coresponding IC in the
code after we are done using them and created .ext file if needed*/
void destroy_externlist(externList* head);

/*----------------------------------------------------------------------------*/
/*function to check machine code overflow in computer memory 100 words of memory
are reserver hence machine code of IC + DC can only be 156 memory word*/
bool is_code_overflow(int IC, int DC);

/*----------------------------------------------------------------------------*/
/*a function to created new code image node of the struct for encoding*/
codeimage* new_code_image();

/*----------------------------------------------------------------------------*/
/*a function to fill word for the encoded IC word*/
void fill_encoded_IC(codeimage* current, unsigned dest,
    unsigned source, unsigned opcode, unsigned param2, unsigned param1);

/*----------------------------------------------------------------------------*/
/*a function to handle and fill encoding for registers*/
void fill_register_word(codeimage* current,
    unsigned dest, unsigned source);

/*----------------------------------------------------------------------------*/
/*a function to handle and fill encoding for lables or parameters of immediate
addressing type*/
void fill_label_or_immediate(codeimage* current, unsigned ARE, unsigned address);

/*----------------------------------------------------------------------------*/
/*a function to handldle data encoding (numbers) in the second pass*/
void encode_data(char *param_line, int data_image[], int *DC);

/*----------------------------------------------------------------------------*/
/*another function to handle data encoding (string) in the second pass*/
void encode_string(char *param_line, int data_image[], int *DC);

/*----------------------------------------------------------------------------*/
/*function to encode parameters in code using a switch case*/
void encode_parameter(codeimage* current, symbol *symbol_table, char* source,
    char *dest, externList** extern_list, int IC);

/*----------------------------------------------------------------------------*/
/*function to insert code image node to code image linked list*/
codeimage* insert_code(codeimage** head);

/*----------------------------------------------------------------------------*/
/*a function to take full line of code and retur it without the lable in the 
beginning if label is present, else returns line as is.*/
char* create_labeless_line(char* line);

/*----------------------------------------------------------------------------*/
/*function to encode instruction lines of code and puting them in the codeimage*/
bool encode_instruction(codeimage** head, symbol *symbol_table, char* line,
                         int *IC, externList** extern_list);

/*----------------------------------------------------------------------------*/
/*functiong to simplify use of all other functions and is used as the main
function to encode line of code*/
bool encode(codeimage** current, symbol **symbol_table, char* line, int* DC, int* IC,
             int data_image[], externList** extern_list);

/*----------------------------------------------------------------------------*/
/*function that writes to file all labels which are entry lables with their 
coresponding IC address to the .ent file*/
void write_entry(symbol* head, char* filename);

/*----------------------------------------------------------------------------*/
/*function to write to write all extern labels in file with coresponding IC 
of the lines they were used in*/
void write_extern(externList* head, char* filename);

/*----------------------------------------------------------------------------*/
/*function to print code image in special binary base, will be used later on in
the write object function*/
void print_codeimage_table(codeimage* head, FILE* filename);

/*----------------------------------------------------------------------------*/
/*functiong to print data image in special binary base, will be used later on
in the write object function*/
void print_dataimage(int data_image[], int DC, int IC, FILE* filename);

/*----------------------------------------------------------------------------*/
/*function to handle the writing of machine language to the .ob file for the 
computer to load to memory and run program*/
void write_object(char* filename, codeimage* current, int DC, int IC, int data_image[]);

#endif /* SECOND_PASS_H */
