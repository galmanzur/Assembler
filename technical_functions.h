#ifndef TECHNICAL_FUNCTIONS_H
#define TECHNICAL_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
/* function to copy the line to the new buffer and remove the label if present
* assuming line is not destroyed */
void extract_params(char buffer[], char new_buffer[]);


/*----------------------------------------------------------------------------*/
/*a function to take full line of code and retur it without the lable in the 
beginning if label is present, else returns line as is.*/
char* remove_label(char* line);

#endif /* TECHNICAL_FUNCTIONS_H */