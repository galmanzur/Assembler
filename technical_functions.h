#ifndef TECHNICAL_FUNCTIONS_H
#define TECHNICAL_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
/*assuming line is not destroyed copying parameters in line*/
void extract_params(char buffer[], char new_buffer[]);

/*----------------------------------------------------------------------------*/
/*function that get index and return the number of parameters*/
/*int param_number(int index); */

#endif /* TECHNICAL_FUNCTIONS_H */