#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <stdio.h>
#include "enable_bool.h"

/*----------------------------------------------------------------------------*/
extern char *extension_file_source; /*variable to store the extension of file as file*/
extern char *extension_file_after_preassembler;  /*varaiable to store the extension of after pre assembler file*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*this file gets a pointer to a file name and checks if available for reading 
and can be opened*/
bool check_file(char* filename);

/*----------------------------------------------------------------------------*/
/*function to add relevant extension for file handlig*/
char* add_extension(char* filename, char* extension);

#endif /* FILE_SERVICE_H */





