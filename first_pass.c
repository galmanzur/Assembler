#include "first_pass.h"

/*----------------------------------------------------------------------------*/
/*the first pass funtion - would validate the assembly syntax and fill symbol table*/
bool call_first_pass(symbol** symbol_table, char *filename, int *IC, int *DC)
{
    int cline = 0;
    bool is_valid = true;
    char buffer[MAX_LENGTH_LINE];
    char buffer_copy[MAX_LENGTH_LINE];
    FILE* file_to_process;
    file_to_process = fopen(filename, "r");
    while(fgets(buffer, MAX_LENGTH_LINE, file_to_process))
    {
        cline++;
        strcpy(buffer_copy, buffer);
        if (is_blank_or_comment(buffer))
            continue;
        if(!validate_all_in_line(buffer, cline, DC, symbol_table))
            is_valid = false;
        else
        {
            printf("DEBUG: Processing line %d => %s\n", cline, buffer_copy);
            process_line(buffer_copy, cline, symbol_table, IC, DC);
            debug_print_symbol_table(*symbol_table);
        }
        printf("DEBUG: Current IC: %d, DC: %d\n", *IC, *DC);
    }
    sync_IC_of_data_symbol(*symbol_table, *IC);
    if(is_there_duplicate_symbol(*symbol_table))
        is_valid = false;
    if(is_valid == false)
    {
        printf("CRITICAL: the assembler found errors. Stopping handling of file \"%s\".\n", filename);
        fclose(file_to_process);
        return false;       
    }
    fclose(file_to_process);
    return is_valid;
}

/*----------------------------------------------------------------------------*/
/*function to get line from code and validate its syntax int the assembly
language*/
bool validate_all_in_line(char* line, int cline, int *DC,  symbol** symbol_table)
{
    char buffer[MAX_LENGTH_LINE] = {0};
    char* word_to_validate;
    char* token;
    int index_opcode;
    char line_copy[MAX_LENGTH_LINE]; 
    char line_copy_for_validate_space[MAX_LENGTH_LINE];
    char line_copy_for_validate_addressing[MAX_LENGTH_LINE];
    char label_name[MAX_LENGTH_LABEL];
    label_name[0] = '\0';

    line = strtok(line, "\r\n"); /* remove new line characters */
    /* Copy the line to line copy */
    strcpy(buffer, line);
    strcpy(line_copy, line);
    strcpy(line_copy_for_validate_space, line);

    /* Label handling */
    word_to_validate = line;
    if (is_label_end_with_colon(word_to_validate))
    {   
        printf("[process_line]: Found word => '%s'\n", word_to_validate);
        token = strchr(word_to_validate, ':');
        *token = 0;
        if (!is_label(word_to_validate, cline))
            return false;
        validate_entry_extern_after_label(line_copy, cline);
        strcpy(label_name, word_to_validate);
        token = (*(token + 1) != 0) ? token + 1 : NULL;
        /*word_to_validate = strtok(token, " \r\t\n");*/
    }
    /* Check if the line is a command */
    if (word_to_validate && is_command(word_to_validate))
    {
        int count_tokens = 0;
        /* copy parameters in line*/
        char new_buffer[MAX_LENGTH_LINE];
        extract_params(buffer, new_buffer);
        extract_params(buffer, line_copy_for_validate_addressing);


        printf("line_copy_3: %s\n", line_copy_for_validate_addressing);
        printf("new_buffer: %s\n", new_buffer);

        /* opcode handling */
        if ((index_opcode = get_opcode(word_to_validate)) != -1)
        {
            char* first_param, *second_param;
            /* Validate line comma and spaces */
            if (!valid_line_comma_spaces(buffer, cline))
                return false;

            /* Validate source operand */
            first_param = strtok(new_buffer, " ,\t\n");
            second_param = strtok(NULL, " \t\n");
            if (validate_addressing_to_received_opcode_param(index_opcode, first_param, SRC, cline))
            {
                if(first_param)
                {
                    count_tokens++;
                    /* Validate source operand */
                    if (!validate_relevantive_addressing(first_param, cline, line_copy_for_validate_addressing))                
                        return false;
                }   
            }
            if (validate_addressing_to_received_opcode_param(index_opcode, second_param, DST, cline))
            {
                if(second_param)  
                {
                    count_tokens++;
                    /* Validate destination operand */
                    if (!validate_relevantive_addressing(second_param, cline, line_copy_for_validate_addressing))
                        return false;
                    while(strtok(NULL, " \t\n") !=NULL)
                        count_tokens++;
                }
            }
            if(count_tokens >= 3)
            {
                printf("ERROR: too many tokens in line %d.\n", cline);
                return false;
            }   
        }
    }

    else if(!validate_space_after_data_or_string(line_copy_for_validate_space, cline))
        return false;

    /* Finish to validate the line */
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

/* This function checks if .entry or .extern appears after a label in the line. If it is, it prints a warning message and returns false. */
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