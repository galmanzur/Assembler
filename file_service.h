/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                                 File Service 📂📑💻
This file contains functions to handle file operations in the assembler.
It includes functions to check if a file is readable, add extensions to file names, and create entry, extern, and object files.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"
#include "symbol_repo.h"
#include "encoding_data.h"
#include "encoding_service.h"
#include "second_pass.h"
#include "enable_bool.h"
#include "data_to_file_service.h"
#include "print_to_console_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* EXTENSIONS of files: */

extern char *extension_file_source; /*variable to store the extension of file as file*/
extern char *extension_file_after_preassembler;  /*varaiable to store the extension of after pre assembler file*/
extern char *fentry;
extern char *fextern;
extern char *fobject;

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a file is readable. 
 * It takes the file name as a parameter and returns true if the file is readable, false otherwise. */
bool is_file_readable(char* filename);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function adds an extension to a file name.
 * It takes the file name and the extension as parameters and returns the new file name with the extension. */
char* add_extension_to_file(char* filename, char* extension);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function writes the entry labels to a file with their corresponding IC address.
 * It takes the head of the symbol table and the file name as parameters. */
void create_entry_file(symbol* head, char* filename);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function writes the external labels and their addresses to a file.
 * It takes the head of the extern list and the file name as parameters. */
void create_extern_file(externList* head, char* filename);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates an object file with the code image and data image.
 * It takes the file name, current code image node, data counter (DC), instruction counter (IC), and data image as parameters. */
void create_object_file(char* filename, codeimage* current, int DC, int IC, int data_image[]);

#endif /* FILE_SERVICE_H */





