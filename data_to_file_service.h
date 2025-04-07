#ifndef DATA_TO_FILE_SERVICE_H
#define DATA_TO_FILE_SERVICE_H

#include "manager.h"
#include "encoding_repo.h"
#include "encoding_data.h"


/*function to print code image in special binary base, will be used later on in
the write object function*/
void write_code_image_to_file(codeimage* head, FILE* file_name);

/*----------------------------------------------------------------------------*/
/*functiong to print data image in special binary base, will be used later on
in the write object function*/
void write_data_image_to_file(int data_image[], int DC, int IC, FILE* file_name);

/*----------------------------------------------------------------------------*/
/* Function to print code image in hexa base */
void write_code_image_to_file_in_hexa(codeimage* head, FILE* file_name);

/*----------------------------------------------------------------------------*/

/* Function to print data image in hexa base */
void write_data_image_to_file_in_hexa(int data_image[], int DC, int IC, FILE* file_name);






#endif /* DATA_TO_FILE_SERVICE_H */