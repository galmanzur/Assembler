#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include "first_pass.h"

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

#endif /* SECOND_PASS_H */
