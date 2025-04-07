#include "second_pass.h"

/*----------------------------------------------------------------------------*/
/*function that used the above function, encodes and validates the code if
all validation passed in first and second pass*/
bool call_second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list)
{
    int cline = 0;
    bool is_valid = true;

    char* file_to_read = add_extenstion_to_file(filename, ".am");

    char buffer[MAX_LINE], buffer_copy[MAX_LINE];
    FILE* pointer_to_file;

    if(!is_file_readable(file_to_read))
    {
        printf("ERROR: File %s is not readable.\n", file_to_read);
        free(file_to_read);
        return false;
    }

    pointer_to_file = fopen(file_to_read, "r");
    (*IC) = 100;
    (*DC) = 0;

    while(fgets(buffer, MAX_LINE, pointer_to_file))
    {
        cline++;
        /* Copy the line to line copy */
        strcpy(buffer_copy, buffer);
        
        /* If the line is blank or a comment, skip it */
        if (is_blank_or_comment(buffer))
            continue;
        else
        {   
            printf("DEBUG: Processing line %d => %s\n", cline, buffer_copy);
            if(!encode_line(current, symbol_table, buffer_copy, DC, IC, data_image, extern_list))
                is_valid = false;          
        }
    }
        if(is_valid)
        {
            create_entry_file(*symbol_table, filename);
            create_object_file(filename, *current, *DC, *IC, data_image);
            create_extern_file(*extern_list, filename);
        }

    free(file_to_read);
    fclose(pointer_to_file);

    return true;
}


void write_code_image_to_file_in_hexa(codeimage* head, FILE* file_name)
{
    int i;
    int IC = 100; /* Starting IC address */

    while(head)
    {
        for(i = 0; i < head->number_of_words; i++)
        {
            unsigned int word = head->encoded_instruction[i].bit & 0xFFFFFF; /* Mask to 24 bits */
            fprintf(file_name, "%07d\t%06X\n", IC++, word);
        }
        head = head->next;
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



/*----------------------------------------------------------------------------*/
/*function to print code image in special binary base, will be used later on in
the write object function*/
void write_code_image_to_file(codeimage* head, FILE* file_name)
{
    int i, j, IC = 100;
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


