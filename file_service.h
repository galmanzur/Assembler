#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include "manager.h"
#include "symbol_repo.h"
#include "encoding_data.h"
#include "second_pass.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enable_bool.h"

#define MAX_FILENAME 255 /*Maximum chars in file name */
/*----------------------------------------------------------------------------*/
extern char *extension_file_source; /*variable to store the extension of file as file*/
extern char *extension_file_after_preassembler;  /*varaiable to store the extension of after pre assembler file*/

extern char *fentry;
extern char *fextern;
extern char *fobject;

/*----------------------------------------------------------------------------*/
/*this file gets a pointer to a file name and checks if available for reading 
and can be opened*/
bool is_file_readable(char* filename);

/*----------------------------------------------------------------------------*/
/*function to add relevant extension for file handlig*/
char* add_extenstion_to_file(char* filename, char* extension);

/*----------------------------------------------------------------------------*/
/*function that writes to file all labels which are entry lables with their 
coresponding IC address to the .ent file*/
void create_entry_file(symbol* head, char* filename);

/*----------------------------------------------------------------------------*/
/*function to write to write all extern labels in file with coresponding IC 
of the lines they were used in*/
void create_extern_file(externList* head, char* filename);

/*----------------------------------------------------------------------------*/
/*function to handle the writing of machine language to the .ob file for the 
computer to load to memory and run program*/
void create_object_file(char* filename, codeimage* current, int DC, int IC, int data_image[]);

#endif /* FILE_SERVICE_H */





