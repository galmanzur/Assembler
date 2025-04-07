#ifndef ENCODING_REPO_H
#define ENCODING_REPO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "encoding_data.h"
#include "encoding_service.h"
#include "manager.h"
#include "enable_bool.h"
#include "print_to_console_service.h"

/*----------------------------------------------------------------------------*/
/*function to check machine code overflow in computer memory 100 words of memory
are reserver hence machine code of IC + DC can only be 156 memory word*/
bool is_code_overflow(int IC, int DC);

/*----------------------------------------------------------------------------*/
/*a function to created new code image node of the struct for encoding*/
codeimage* create_code_image();

/*----------------------------------------------------------------------------*/
/*function to insert code image node to code image linked list*/
codeimage* insert_code(codeimage** head);

/*----------------------------------------------------------------------------*/
/*function to destroy the code image after we are done using it*/
void free_code_image(codeimage* head);

/*----------------------------------------------------------------------------*/
/*function to desytoy list of the extern labels and their coresponding IC in the
code after we are done using them and created .ext file if needed*/
void free_extern_list(externList* head);








#endif /* ENCODING_REPO_H */