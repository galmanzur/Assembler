#include "second_pass.h"

/*----------------------------------------------------------------------------*/
/*function that used the above function, encodes and validates the code if
all validation passed in first and second pass*/
bool second_pass(char* filename, codeimage** current, symbol **symbol_table,
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
            if(!encode(current, symbol_table, buffer_copy, DC, IC, data_image, extern_list))
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

/*----------------------------------------------------------------------------*/
/*a function to take full line of code and retur it without the lable in the 
beginning if label is present, else returns line as is.*/
char* remove_label(char* line)
{
    char* ptr = strchr(line, ':');
    if(ptr)
        return (ptr + 1);
    while(isspace(*line))
        line++;
    return line;
}

/*----------------------------------------------------------------------------*/
/*function to print code image in special binary base, will be used later on in
the write object function*/
void print_codeimage_table(codeimage* head, FILE* filename)
{
    int i, j, IC = 100;
    while(head)
    {
        for(i = 0; i < head->L; i++)
        {
            unsigned int word = head->encoded_instruction[i].bit;
            fprintf(filename, "0%d\t",IC++);
            for( j = 13; j >= 0; j--)
            {
                fprintf(filename, "%c", (((word >> j) & 1) == 0)?'0':'1');
            }
            fprintf(filename, "\n");
        }
        head = head->next;
    }
}

/*----------------------------------------------------------------------------*/
/*functiong to print data image in special binary base, will be used later on
in the write object function*/
void print_dataimage(int data_image[], int DC, int IC, FILE* filename)
{
    int i, j;
    for(i = 0; i < DC; i++)
    {
        fprintf(filename, "0%d\t", i + IC);
        for( j = 13; j >= 0; j--)
        {
            fprintf(filename, "%c", (((data_image[i] >> j) & 1) == 0)?'.':'/');
        }
        fprintf(filename, "\n");
    }
}


