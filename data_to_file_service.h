/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                               ** Data to File Service 📂 **
 * This file contains functions to write the code and data images to a file in binary and hexa formats.
 * The functions are used to generate the object file for the assembler.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef DATA_TO_FILE_SERVICE_H
#define DATA_TO_FILE_SERVICE_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "manager.h"
#include "encoding_repo.h"
#include "encoding_data.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function writes the code image to a file in Hexa format.
 * It takes the head of the code image linked list and the file pointer as parameters. */
void write_code_image_to_file_in_hexa(codeimage* head, FILE* file_name);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function writes the data image to a file in Hexa format.
 * It takes the data image array, the data counter (DC), the instruction counter (IC), and the file pointer as parameters. */
void write_data_image_to_file_in_hexa(int data_image[], int DC, int IC, FILE* file_name);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* DATA_TO_FILE_SERVICE_H */