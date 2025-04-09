#include "data_to_file_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function writes the code image to a file in Hexa format.
 * It takes the head of the code image linked list and the file pointer as parameters. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function writes the data image to a file in Hexa format.
 * It takes the data image array, the data counter (DC), the instruction counter (IC), and the file pointer as parameters. */
void write_data_image_to_file_in_hexa(int data_image[], int DC, int IC, FILE* file_name)
{
    int i;
    for(i = START_VALUE_OF_DC ; i < DC; i++)
    {
        unsigned int word = data_image[i] & 0xFFFFFF; /* Mask to 24 bits */
        fprintf(file_name, "%07d\t%06x\n", i + IC, word);
    }
}