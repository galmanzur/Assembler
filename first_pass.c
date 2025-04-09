#include "first_pass.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function performs the first pass of the assembler. 
 * It processes the assembly code, validates the syntax, and builds the symbol table.
 * It takes the symbol table, file name, instruction counter (IC), and data counter (DC) as parameters.
 * It returns true if the first pass was successful, false otherwise. */
bool call_first_pass(symbol** symbol_table, char *filename, int *IC, int *DC)
{
    int current_line = 0;
    bool is_valid = true;
    char buffer[MAX_LENGTH_LINE];
    char buffer_copy[MAX_LENGTH_LINE];
    FILE* file_to_process;
    file_to_process = fopen(filename, "r");
    while(fgets(buffer, MAX_LENGTH_LINE, file_to_process))
    {
        current_line++;
        strcpy(buffer_copy, buffer);
        if (is_blank_or_comment(buffer))
            continue;
        if(!validate_all_in_line(buffer, current_line, DC, symbol_table))
            is_valid = false;
        else
        {
            process_line(buffer_copy, current_line, symbol_table, IC, DC);
            debug_print_symbol_table(*symbol_table);
        }
    }
    sync_IC_of_data_symbol(*symbol_table, *IC);
    if(is_there_duplicate_symbol(*symbol_table))
        is_valid = false;
    if(is_valid == false)
    {
        fclose(file_to_process);
        return false;       
    }
    fclose(file_to_process);
    return is_valid;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function validate the line syntax in the assembly language.
 * It takes the line, current line number (current_line), data counter (DC), and symbol table as parameters.
 * It returns true if the line is valid, false otherwise. */
bool validate_all_in_line(char* line, int current_line, int *DC,  symbol** symbol_table)
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
        token = strchr(word_to_validate, ':');
        *token = 0;
        if (!is_label(word_to_validate, current_line))
            return false;

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

        /* opcode handling */
        if ((index_opcode = get_opcode(word_to_validate)) != -1)
        {
            char* first_param, *second_param;
            /* Validate line comma and spaces */
            if (!valid_line_comma_spaces(buffer, current_line))
                return false;

            /* Validate source operand */
            first_param = strtok(new_buffer, " ,\t\n");
            second_param = strtok(NULL, " \t\n");

            /* Validate destination operand, 0 means that there is it the source parameter */
            if (validate_addressing_to_received_opcode_param(index_opcode, first_param, 0, current_line))
            {
                if(first_param)
                {
                    count_tokens++;
                    /* Validate source operand */
                    if (!validate_addressing_of_opcode(first_param, current_line, line_copy_for_validate_addressing))                
                        return false;
                }   
            }

            /* Validate destination operand, 1 means that there is it the dest parameter */
            if (validate_addressing_to_received_opcode_param(index_opcode, second_param, 1, current_line))
            {
                if(second_param)  
                {
                    count_tokens++;
                    /* Validate destination operand */
                    if (!validate_addressing_of_opcode(second_param, current_line, line_copy_for_validate_addressing))
                        return false;
                    while(strtok(NULL, " \t\n") !=NULL)
                        count_tokens++;
                }
            }
            if(count_tokens >= 3)
            {
                print_error(current_line, "Too many tokens in line.");
                return false;
            }   
        }
    }

    else if(!validate_space_after_data_or_string(line_copy_for_validate_space, current_line))
        return false;

    /* Finish to validate the line */
    return true;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function validate that there is a space after the data or string directive in the line.
 * It takes the line and current line number (current_line) as parameters.
 * It returns true if pass the validation, false otherwise. */
bool validate_space_after_data_or_string(char line[], int current_line)
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
            print_error(current_line, "expected space after .string in line.");
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
            print_error(current_line, "expected space after .data in line.");
            return false;
        }
    }
    return true;
}

