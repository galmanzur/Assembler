#include "first_pass.h"

/*----------------------------------------------------------------------------*/
/*the first pass funtion - would validate the assembly syntax and fill symbol table*/
bool call_first_pass(symbol** symbol_table, char *filename, int *IC, int *DC)
{
    int cline = 0;
    bool is_valid = true;
    char buffer[MAX_LINE];
    char buffer_copy[MAX_LINE];
    FILE* fptr;
    fptr = fopen(filename, "r");
    while(fgets(buffer, MAX_LINE, fptr))
    {
        cline++;
        strcpy(buffer_copy, buffer);
        if (is_blank_or_comment(buffer))
            continue;
        if(!process_line(buffer, cline, DC, symbol_table))
            is_valid = false;
        else
        {
            printf("DEBUG: Processing line %d => %s\n", cline, buffer_copy);
            handle_symbol_in_line(buffer_copy, cline, symbol_table, IC, DC);
            debug_print_symbol_table(*symbol_table);
        }
        printf("DEBUG: Current IC: %d, DC: %d\n", *IC, *DC);
    }
    update_symbol_address(*symbol_table, *IC);
    if(is_there_duplicate_symbol(*symbol_table))
        is_valid = false;
    if(is_valid == false)
    {
        printf("CRITICAL: the assembler found errors. Stopping handling of file \"%s\".\n", filename);
        fclose(fptr);
        return false;       
    }
    fclose(fptr);
    return is_valid;
}

/*----------------------------------------------------------------------------*/
/*function to get line from code and validate its syntax int the assembly
language*/
bool process_line(char* line, int cline, int *DC,  symbol** symbol_table)
{
    char buffer[MAX_LINE] = {0};
    char* word;
    char* token;
    int index;
    char line_copy[MAX_LINE]; 
    char line_copy_2[MAX_LINE];
    char line_copy_3[MAX_LINE];
    char label_name[MAX_LABEL];
    label_name[0] = '\0';

    /* Copy the line to line copy */
    strcpy(buffer, line);
    strcpy(line_copy, line);
    strcpy(line_copy_2, line);

    /* Label handling */
    word = strtok(line, "\t\n\r");
    if (is_label_end_with_colon(word))
    {   
        printf("[process_line]: Found word => '%s'\n", word);
        token = strchr(word, ':');
        *token = 0;
        if (!is_safe_label(word, cline))
            return false;
        validate_entry_extern_after_label(line_copy, cline);
        strcpy(label_name, word);
        token = (*(token + 1) != 0) ? token + 1 : NULL;
        word = strtok(token, " \t\n");
    }

    /* Check if the line is a command */
    if (word && is_command(word))
    {
        int tok_count = 0;
        /* copy parameters in line*/
        char new_buffer[MAX_LINE];
        extract_params(buffer, new_buffer);
        extract_params(buffer, line_copy_3);


        printf("line_copy_3: %s\n", line_copy_3);
        printf("new_buffer: %s\n", new_buffer);

        /* opcode handling */
        if ((index = get_opcode(word)) != -1)
        {
            char* param1, *param2;
            /* Validate line comma and spaces */
            if (!valid_line_comma_spaces(buffer, cline))
                return false;

            /* Validate source operand */
            param1 = strtok(new_buffer, " ,\t\n");
            param2 = strtok(NULL, " \t\n");
            if (validate_addressing_type(index, param1, SRC, cline))
            {
                if(param1)
                {
                    tok_count++;
                    /* Validate source operand */
                    if (!validate_addressing(param1, cline, line_copy_3))                
                        return false;
                }   
            }
            if (validate_addressing_type(index, param2, DST, cline))
            {
                if(param2)  
                {
                    tok_count++;
                    /* Validate destination operand */
                    if (!validate_addressing(param2, cline, line_copy_3))
                        return false;
                    while(strtok(NULL, " \t\n") !=NULL)
                        tok_count++;
                }
            }
            if(tok_count >= 3)
            {
                printf("ERROR: too many tokens in line %d.\n", cline);
                return false;
            }   
        }
    }
    else if(!validate_space_after_data_or_string(line_copy_2, cline))
        return false;
    /* line does not contain a command */
    return true;
}


/*----------------------------------------------------------------------------*/

/*a function assuming only .data or .string can apear in line*/
bool validate_space_after_data_or_string(char line[], int cline)
{
    char* string_ptr = strstr(line, ".string");
    char* data_ptr = strstr(line, ".data");
    if (string_ptr)
    {
        int len = strlen(".string");
        if (isspace(string_ptr[len]))
            return true;
        else
        {
            printf("ERROR: expected space after .string in line %d.\n", cline);
            return false;
        }
    }
    else if (data_ptr)
    {
        int len = strlen(".data");
        if (isspace(data_ptr[len]))
            return true;
        else
        {
            printf("ERROR: expected space after .data in line %d.\n", cline);
            return false;
        }
    }
    return true;
}

/*----------------------------------------------------------------------------*/

/*assuming : exist beacuse was handled before hand*/
char validate_entry_extern_after_label(char line[], int cline)
{
    char* colon_ptr = strstr(line, ":");
    if (colon_ptr != NULL)
    {
        colon_ptr++;
        while (isspace(*colon_ptr))
            colon_ptr++;

        if (strncmp(colon_ptr, ".extern", 7) == 0)
        {
            printf("WARNING: .extern after label in line %d.\n", cline);
            return false;
        }
        else if (strncmp(colon_ptr, ".entry", 6) == 0)
        {
            printf("WARNING: .entry after label in line %d.\n", cline);
            return false;
        }
    }
    return true;
}