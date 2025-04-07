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

    char buffer[MAX_LENGTH_LINE], buffer_copy[MAX_LENGTH_LINE];
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

    while(fgets(buffer, MAX_LENGTH_LINE, pointer_to_file))
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
