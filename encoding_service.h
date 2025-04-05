#ifndef ENCODING_SERVICE_H
#define ENCODING_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "manager.h"
#include "addressing_service.h"
#include "encoding_data.h"
#include "symbol_repo.h"
#include "second_pass.h"
#include "enable_bool.h"
#include "technical_functions.h"

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
    unsigned source, unsigned opcode, unsigned register_dest, unsigned register_source);

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
/*function to destroy the code image after we are done using it*/
void free_code_image(codeimage* head);

/*----------------------------------------------------------------------------*/
/*function to desytoy list of the extern labels and their coresponding IC in the
code after we are done using them and created .ext file if needed*/
void free_external_list(externList* head);

/*----------------------------------------------------------------------------*/
/*function to encode instruction lines of code and puting them in the codeimage*/
bool encode_instruction(codeimage** head, symbol *symbol_table, char* line,
    int *IC, externList** extern_list);

/*----------------------------------------------------------------------------*/
/*functiong to simplify use of all other functions and is used as the main
function to encode line of code*/
bool encode(codeimage** current, symbol **symbol_table, char* line, int* DC, int* IC,
int data_image[], externList** extern_list);



#endif /* ENCODING_SERVICE_H */


