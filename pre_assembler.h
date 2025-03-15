#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include "macro_repo.h"
#include "assembler_data.h"
#include "enable_bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*----------------------------------------------------------------------------*/
/*funciton to spread and validate the macros in file with macros*/
void call_pre_assembler(char *input_file, char *output_file);

#endif /* PRE_ASSEMBLER_H */


