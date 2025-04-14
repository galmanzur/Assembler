#include "process_data.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function processes a line of code and handles the string directive statement.
 * It takes the string, current line number, and data counter as parameters.
 * It returns true if the processing was successful, false otherwise. */
int handle_string_directive_statement(char *str, int current_line, int *DC)
{
    int DC_to_update = *DC;
	size_t i, j;

    if (str == NULL)
    {
        print_error(current_line, "Received NULL and not a string in line.");
    	return -1;	
    }
    for(i = 0; isspace(str[i]) && str[i]; i++); 
    for(j = strlen(str) - 1; isspace(str[j]) && j >= i ; j--); 
    if (str[i] != '\"')
    {
        print_error(current_line, "Invalid string, does not start with \"");
        return -1;
    }
    for (i++; str[i] != '\"' && str[i] != '\0'; i++)
    {
        if (!is_ascii(str[i]))
        {
            print_error(current_line, "Invalid string, not all characters are ASCII.");
            return -1;
        }
    }
    if (str[j] != '\"')
    {
        print_error(current_line, "Invalid string, does not end with \".");
        return -1;
    }

    /* subtract 4 for:
     the quotes and each of "/"  */
    (*DC) += (strlen(str)-2); 
    return DC_to_update;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function processes a line of code and handles the string directive statement.
 * It takes the string, current line number, and data counter as parameters.
 * It returns true if the processing was successful, false otherwise. */
int handle_data_directive_statement(char* line, int current_line, int *DC)
{   
    char buffer[MAX_LENGTH_LINE];
    char* token;
    int init_DC = *DC;
    int num_tokens = 0;
    int num_commas = 0;
    int num_numbers = 0;

    /* copy the line to the buffer */
    strcpy(buffer, line);
    /* count the number of tokens, commas, and numbers in the line */
    token = strtok(buffer, " ,\r\t\n");

    while (token != NULL)
    {
        num_tokens++;
        if (is_legal_number(token))
              num_numbers++;
        else
        {
            /* check for invalid characters in the token */
            size_t i, len = strlen(token);
            for (i = 0; i < len; i++)
            {
                if (!isdigit(token[i]) && !isspace(token[i]) && token[i] != '+' && token[i] != '-')
                {
                    print_error(current_line, "Invalid character in data parameter.");
                    return -1;
                }
            }
        }
        token = strtok(NULL, " ,\r\t\n");
    }

    /* check for invalid number of tokens */
    if (num_tokens == 0)
    {
        print_error(current_line, "No parameters in data directive.");
        return -1;
    }

    /* check for invalid number of numbers */
    if (num_numbers == 0)
    {
        print_error(current_line, "No numbers in data directive.");
        return -1;
    }

    /* check for invalid comma placement */
    token = line;
    while (*token != '\0')
    {
        if (*token == ',')
        {
            num_commas++;
            /* skip over any spaces */
            do
            {
                token++;
            } while (*token == ' ');

            if (*token == '\0')
            {
                print_error(current_line, "Invalid comma placement in data directive.");
                return -1;
            }
        }
        token++;
    }
    if (num_commas != num_tokens - 1)
    {
        print_error(current_line, "Invalid comma placement in data directive.");
        return -1;
    }
    (*DC) += num_numbers;
    return init_DC;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function processes a line - it checks if line is opcode or directive and handles it accordingly.
 * It returns true if the processing was successful, false otherwise. */
bool process_line(char* line, int current_line, symbol** symbol_table, int *IC, int *DC)
{
    /*int how_much_params_in_line;*/
    symbol* new_symbol;
    int DC_to_update;
    int IC_to_update = *IC;
    char buffer[MAX_LENGTH_LINE] = {0};
    char* word;
    char* token;
    int index_opcode;
    directive_type directive_type;
    char buffer_copy[MAX_LENGTH_LINE] = {0};
    char buffer_copy_1[MAX_LENGTH_LINE]  = {0}; 
    char buffer_copy_2[MAX_LENGTH_LINE]= {0};
    char buffer_copy_3[MAX_LENGTH_LINE]= {0};
    char buffer_copy_5[MAX_LENGTH_LINE]= {0};
    char label_name[MAX_LENGTH_LABEL]= {0};

    line = strtok(line, "\r\t\n"); /* remove new line characters */
    /* DEBUG: Print the incoming line */

    /* Copy the line to local buffers for different parsing needs */
    strcpy(buffer,line);
    strcpy(buffer_copy_1, line);
    strcpy(buffer_copy_2,line);
    strcpy(buffer_copy_5,line);

    /*-----------------------------------------------------*/
    /* Label handling */
    /*-----------------------------------------------------*/
    word = strtok(line, " ,\t\n\r");

    if (is_label_end_with_colon(word))
    {   
        token = strchr(word, ':');
        *token = 0;

        strcpy(label_name, word);

        /* Move past the colon if there's more text on the same token */
        token = (*(token + 1) != 0) ? token + 1 : NULL;
        word = strtok(token, " \t\n\r");
    }

    /*-----------------------------------------------------*/
    /* Command or directive handling */
    /*-----------------------------------------------------*/
    if (word && is_command(word))
    {
        int counter_tokens = 0;
        /* Copy parameters in line (operands) */
        extract_params(buffer, buffer_copy);
        extract_params(buffer, buffer_copy_3);

        /*-------------------------------------------------*/
        /* Opcode handling ❕ */
        /*-------------------------------------------------*/
        if ((index_opcode = get_opcode(word)) != -1)
        {
            char *param1_of_opcode = NULL, *param2_of_opcode = NULL;

            /* Each valid command requires at least one word in memory */
            (*IC)++;

            if (strstr(buffer_copy, ","))
            {
                /* We only have two operands separated by a comma */
                param1_of_opcode = strtok(buffer_copy, " ,\r\t\n");
                param2_of_opcode = strtok(NULL, " \r\t\n");
            }
            else
            {
                /* Only one operand or none */
                param1_of_opcode = strtok(buffer_copy, " \r\t\n");
            }
                   
            /* how_much_params_in_line = 0; */    
             /* Handle param1 - for add to IC  if param1 was not a register - not direct register addressing */
            if (param1_of_opcode)
            {
                /* Increment the number of tokens */
                counter_tokens++;
                if (!is_register_in_assembler(param1_of_opcode))
                    (*IC)++;
            }

            /* Handle param2 - for add to IC  if param1 was not a register - not direct register addressing */
            if (param2_of_opcode)
            {
                /* Increment the number of tokens */
                counter_tokens++;
                if (!is_register_in_assembler(param2_of_opcode))
                    (*IC)++;
            }

            /* If label found, add or update its symbol entry */
            if (label_name[0] != '\0')
            {
                symbol* symbol_to_add = find_symbol(*symbol_table, label_name);
                if (symbol_to_add) /* symbol alredy exists. */
                    symbol_to_add->address = IC_to_update;  /* Update the symbol's address and mark it as code */
                else
                    add_symbol(symbol_table, label_name, IC_to_update); /* If the symbol doesn't exist, add it with address IC */
            }
        }
        /*-------------------------------------------------*/
        /* Directive handling 💡 */
        /*-------------------------------------------------*/
        else if ((directive_type = get_directive_in_line(word)) != -1)
        {
            switch (directive_type)
            {
                case DIRECTIVE_DATA:
                    DC_to_update = handle_data_directive_statement(buffer_copy, current_line, DC);
                    if (DC_to_update == -1)
                        return false;

                    new_symbol = find_symbol(*symbol_table, label_name);
                    if (new_symbol)
                    {
                        new_symbol->isData  = true;
                        new_symbol->address = DC_to_update;
                    }
                    else if(label_name[0] != '\0')
                    {
                        add_symbol(symbol_table, label_name, DC_to_update);
                        (find_symbol(*symbol_table, label_name))->isData = true;
                    }
                    break;
                    
                case DIRECTIVE_STRING: 
                DC_to_update = handle_string_directive_statement(buffer_copy, current_line, DC);
                    if (DC_to_update == -1)
                        return false;

                    new_symbol = find_symbol(*symbol_table, label_name);
                    if (new_symbol)
                    {
                        new_symbol->isData  = true;
                        new_symbol->address = DC_to_update;
                    }
                    else if(label_name[0] != '\0')
                    {
                        add_symbol(symbol_table, label_name, DC_to_update);
                        (find_symbol(*symbol_table, label_name))->isData = true;
                    }   
                    break;

                case DIRECTIVE_ENTRY:
                    /* use line_copy for .entry handling */
                    
                    word = strtok(buffer_copy_5, " \r\t\n"); /* skip .entry? or label? */
                    word = strtok(NULL, " \r\t\n"); /* actual symbol after .entry */

                    if (word)
                    {
                        word[strcspn(word, " \r\t\n")] = '\0'; /* remove newline */                        
                        new_symbol = find_symbol(*symbol_table, word);
                        if (new_symbol)
                            new_symbol->isEntry = true;
                        else
                        {
                            /* If the symbol doesn't exist, we add it with address IC */
                            add_symbol(symbol_table, word, *IC);
                            (find_symbol(*symbol_table, word))->isEntry = true;
                        }
                    }
                    break;
                case DIRECTIVE_EXTERN:
                    word = strtok(buffer_copy_5, " \t\r\n");
                    word = strtok(NULL, " \t\r\n"); /* symbol after .extern */
                    if (word)
                    {
                        
                        word[strcspn(word, " \t\r\n")] = '\0'; /* remove newline */
                        
                        new_symbol = add_symbol(symbol_table, word, 0);
                        new_symbol->isExternal = true;
                    }
                    break;   
                default:
                    break;
            }
        }
    
    }
    return true;

}


