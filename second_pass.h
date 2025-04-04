#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "file_service.h"
#include "symbol_repo.h"
#include "assembler_data.h"
#include "enable_bool.h"
#include "addressing_service.h"
#include "parser.h"
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

#endif /* SECOND_PASS_H */
