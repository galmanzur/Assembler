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
#include "print_to_console_service.h"
#include "encoding_data.h"
#include "debug.h"
#include <stdio.h>


/*----------------------------------------------------------------------------*/
/*function to hanlde th second pass in this two pass assembler*/
bool call_second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list);

#endif /* SECOND_PASS_H */
