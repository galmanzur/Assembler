#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "manager.h"
#include "file_service.h"
#include "encoding_service.h"
#include "enable_bool.h"
#include "encoding_repo.h"
#include "addressing_service.h"
#include "parser.h"
#include "encoding_data.h"
#include "symbol_defenition.h"
#include "debug.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/*function to hanlde th second pass in this two pass assembler*/
bool call_second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list);

/*----------------------------------------------------------------------------*/
/*function to print code image in special binary base, will be used later on in
the write object function*/
void write_code_image_to_file(codeimage* head, FILE* file_name);

/*----------------------------------------------------------------------------*/
/*functiong to print data image in special binary base, will be used later on
in the write object function*/
void write_data_image_to_file(int data_image[], int DC, int IC, FILE* file_name);


/*----------------------------------------------------------------------------*/
/* Function to print code image in hexa base */
void write_code_image_to_file_in_hexa(codeimage* head, FILE* file_name);

/* Function to print data image in hexa base */
void write_data_image_to_file_in_hexa(int data_image[], int DC, int IC, FILE* file_name);




#endif /* SECOND_PASS_H */
