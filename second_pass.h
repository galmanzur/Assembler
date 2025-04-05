#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "manager.h"
#include "file_service.h"
#include "encoding_service.h"
#include "enable_bool.h"
#include "addressing_service.h"
#include "parser.h"
#include "encoding_data.h"
#include "symbol_defenition.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/*function to hanlde th second pass in this two pass assembler*/
bool second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list);
 
/*----------------------------------------------------------------------------*/
/*a function to take full line of code and retur it without the lable in the 
beginning if label is present, else returns line as is.*/
char* remove_label(char* line);

/*----------------------------------------------------------------------------*/
/*function to print code image in special binary base, will be used later on in
the write object function*/
void print_codeimage_table(codeimage* head, FILE* filename);

/*----------------------------------------------------------------------------*/
/*functiong to print data image in special binary base, will be used later on
in the write object function*/
void print_dataimage(int data_image[], int DC, int IC, FILE* filename);


#endif /* SECOND_PASS_H */
