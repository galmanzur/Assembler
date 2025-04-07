#include "data_to_file_service.h"

void write_code_image_to_file_in_hexa(codeimage* head, FILE* file_name)
{
    int i;
    int IC = START_VALUE_OF_IC; /* Starting IC address */

    while(head)
    {
        for(i = 0; i < head->number_of_words; i++)
        {
            unsigned int word = head->encoded_instruction[i].bit & 0xFFFFFF; /* Mask to 24 bits */
            fprintf(file_name, "%07d\t%06x\n", IC++, word);
        }
        head = head->next;
    }
}

/*----------------------------------------------------------------------------*/
/*function to print code image in special binary base, will be used later on in
the write object function*/
void write_code_image_to_file(codeimage* head, FILE* file_name)
{
    int i, j, IC = START_VALUE_OF_IC;
    while(head)
    {
        for(i = 0; i < head->number_of_words; i++)
        {
            unsigned int word = head->encoded_instruction[i].bit;
            fprintf(file_name, "0%d\t",IC++);
            for( j = SIZE_OF_WORD - 1; j >= 0; j--)
            {
                fprintf(file_name, "%c", (((word >> j) & 1) == 0)?'0':'1');
            }
            fprintf(file_name, "\n");
        }
        head = head->next;
    }
}

/*----------------------------------------------------------------------------*/
/*functiong to print data image in special binary base, will be used later on
in the write object function*/
void write_data_image_to_file(int data_image[], int DC, int IC, FILE* file_name)
{
    int i, j;
    for(i = 0; i < DC; i++)
    {
        fprintf(file_name, "0%d\t", i + IC);
        for( j = SIZE_OF_WORD - 1; j >= 0; j--)
        {
            fprintf(file_name, "%c", (((data_image[i] >> j) & 1) == 0)?'0':'1');
        }
        fprintf(file_name, "\n");
    }
}

void write_data_image_to_file_in_hexa(int data_image[], int DC, int IC, FILE* file_name)
{
    int i;
    for(i = 0; i < DC; i++)
    {
        unsigned int word = data_image[i] & 0xFFFFFF; /* Mask to 24 bits */
        fprintf(file_name, "%07d\t%06X\n", i + IC, word);
    }
}