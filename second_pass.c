#include "second_pass.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function is responsible for the second pass of the assembler. 
 * It processes the assembly code, encodes the instructions and data, and generates the final object file.
 * It takes the file name, head code image node, symbol table, instruction counter (IC), data counter (DC), data image array, and extern list as parameters.
 * It returns true if the second pass was successful, false otherwise. */
bool call_second_pass(char* filename, codeimage** code_image, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list)
{
    int current_line = 0;
    bool is_valid = true;

    char* file_to_read = add_extension_to_file(filename, ".am");

    char buffer[MAX_LENGTH_LINE], buffer_copy[MAX_LENGTH_LINE];
    FILE* pointer_to_file;

    if(!is_file_readable(file_to_read))
    {
        print_global_error("File is not readable.");
        free(file_to_read);
        return false;
    }

    pointer_to_file = fopen(file_to_read, "r");
    (*IC) = START_VALUE_OF_IC;
    (*DC) = START_VALUE_OF_DC;

    while(fgets(buffer, MAX_LENGTH_LINE, pointer_to_file))
    {
        current_line++;
        /* Copy the line to line copy */
        strcpy(buffer_copy, buffer);
        
        /* If the line is blank or a comment, skip it */
        if (is_blank_or_comment(buffer))
            continue;
        else
        {   
            if(!encode_line(code_image, symbol_table, buffer_copy, DC, IC, data_image, extern_list, current_line))
                is_valid = false;          
        }
    }
        if(is_valid)
        {
            create_entry_file(*symbol_table, filename);
            create_object_file(filename, *code_image, *DC, *IC, data_image);
            create_extern_file(*extern_list, filename);
        }

    free(file_to_read);
    fclose(pointer_to_file);

    return is_valid;
}
