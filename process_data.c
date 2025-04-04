#include "process_data.h"

/*a fucntion to validate a string strats and ends with ", and the charactets
inside the "" are all ascii, gets string and line
assuming we get string parameter*/
int handle_string_statement(char *str, int cline, int *DC)
{
    int DC_to_update = *DC;
	size_t i, j;
    printf("[handle_string_statement]: handle_string_statement called with str: %s\n", str);
    if (str == NULL)
    {
    	printf("ERROR: NULL string in line %d.\n", cline);
    	return -1;	
    }
    for(i = 0; isspace(str[i]) && str[i]; i++); 
    for(j = strlen(str) - 1; isspace(str[j]) && j >= i ; j--); 
    if (str[i] != '\"')
    {
        printf("ERROR: invalid string, does not start with \" in line %d.\n", cline);
        return -1;
    }
    for (i++; str[i] != '\"' && str[i] != '\0'; i++)
    {
        if (!is_ascii(str[i]))
        {
            printf("ERROR: invalid string, not all characters are ASCII in line %d.\n", cline);
            return -1;
        }
    }
    if (str[j] != '\"')
    {
        printf("ERROR: invalid string, does not end with \" in line %d.\n", cline);
        return -1;
    }
    printf("[handle_string_statement] string: %s\n", str);  
    printf("up by string length: %d\n", (int)(strlen(str)-4)); /*subtract 2 for the quotes*/
    (*DC) += (strlen(str)-4); /*subtract 4 for the quotes and // */
    printf("[handle_string_statement]:  DC= %d\n", DC_to_update);
    return DC_to_update;
}


/*assuming opcode was handled before hand and already checked for unnecessary 
comma at the beginning and end of line, line is destructable
function to validate a data parameter */
int handle_data_statement(char* line, int cline, int *DC)
{   
    char buffer[MAX_LINE];
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
                    printf("ERROR: invalid character in data parameter at line %d.\n", cline);
                    return -1;
                }
            }
        }
        token = strtok(NULL, " ,\r\t\n");
    }

    /* check for invalid number of tokens */
    if (num_tokens == 0)
    {
        printf("ERROR: no tokens in data parameter at line %d.\n", cline);
        return -1;
    }

    /* check for invalid number of numbers */
    if (num_numbers == 0)
    {
        printf("ERROR: no numbers in data parameter at line %d.\n", cline);
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
                printf("ERROR: invalid comma placement in data parameter at line %d.\n", cline);
                return -1;
            }
        }
        token++;
    }
    if (num_commas != num_tokens - 1)
    {
        printf("ERROR: invalid comma placement in data parameter at line %d.\n", cline);
        return -1;
    }
    (*DC) += num_numbers;
    return init_DC;
}

/*----------------------------------------------------------------------------
 * This function is part of the first pass of the assembler.
 * Its purpose is to process a given line (already passed syntax validation)
 * and add any label (symbol) from the line to the symbol table with the
 * appropriate address and properties. The function also updates the
 * instruction counter (IC) and data counter (DC) as needed.
 *--------------------------------------------------------------------------*/
bool handle_symbol_in_line(char* line, int cline, symbol** symbol_table, int *IC, int *DC)
{
    int param_number = 0;
    symbol* new_symbol;
    int DC_to_update;
    int IC_to_update = *IC;
    char buffer[MAX_LINE] = {0};
    char* word;
    char* token;
    int index;
    char line_copy[MAX_LINE]  = {0}; 
    char line_copy_2[MAX_LINE]= {0};
    char line_copy_3[MAX_LINE]= {0};
    char line_copy_4[MAX_LINE]= {0};
    char label_name[MAX_LABEL]= {0};
    char new_buffer[MAX_LINE] = {0};

    /* DEBUG: Print the incoming line */
    printf("DEBUG: [handle_symbol_in_line] line %d => '%s'\n", cline, line);

    /* Copy the line to local buffers for different parsing needs */
    strcpy(buffer,line);
    strcpy(line_copy, line);
    strcpy(line_copy_2,line);
    strcpy(line_copy_4,line);

    /*-----------------------------------------------------*/
    /* Label handling */
    /*-----------------------------------------------------*/
    word = strtok(line, " ,\t\n\r");

    if (is_label_end_with_colon(word))
    {   
        token = strchr(word, ':');
        *token = 0;

        /* DEBUG: Show the label we found */
        printf("[handle_symbol_line]: Found label => '%s'\n", word);

        strcpy(label_name, word);

        /* Move past the colon if there's more text on the same token */
        token = (*(token + 1) != 0) ? token + 1 : NULL;
        word = strtok(token, " \t\n\r");

        /* DEBUG: Next token after label (possibly command or directive) */
        printf("DEBUG: Next token after label => '%s'\n", (word ? word : "NULL"));
    }
    else
    {
        /* DEBUG: No label found on this line (or 'word' is NULL) */
        printf("DEBUG: No label found at the start of the line.\n");
    }

    /*-----------------------------------------------------*/
    /* Command or directive handling */
    /*-----------------------------------------------------*/
    if (word && is_command(word))
    {
        bool param1_reg = false;
        bool param2_reg = false;
        int counter_tokens = 0;

        /* DEBUG: The line appears to have a command => print it */
        printf("DEBUG: Identified command => '%s'\n", word);

        /* Copy parameters in line (operands) */
        extract_params(buffer, new_buffer);
        extract_params(buffer, line_copy_3);

        /* DEBUG: Show what was extracted */
        printf("DEBUG: new_buffer => '%s'\n", new_buffer);
        printf("DEBUG: line_copy_3 => '%s'\n", line_copy_3);

        /*-------------------------------------------------*/
        /* Opcode handling */
        /*-------------------------------------------------*/
        if ((index = get_opcode(word)) != -1)
        {
            char *param1_of_opcode = NULL, *param2_of_opcode = NULL;

            /* DEBUG: Print opcode index */
            printf("DEBUG: Opcode '%s' found (index = %d)\n", word, index);

            /* Each valid command requires at least one word in memory */
            (*IC)++;
            printf("DEBUG: IC incremented by 1 for the opcode. IC = %d\n", *IC);

            if (strstr(new_buffer, ","))
            {
                /* We only have two operands separated by a comma */
                param1_of_opcode = strtok(new_buffer, " ,\r\t\n");
                param2_of_opcode = strtok(NULL, " \r\t\n");
            }
            else
            {
                /* Only one operand or none */
                param1_of_opcode = strtok(new_buffer, " \r\t\n");
            }

            /* DEBUG: Print out the operands we found */
            printf("DEBUG: param1='%s', param2='%s'\n",
                   (param1_of_opcode ? param1_of_opcode : "NULL"),
                   (param2_of_opcode ? param2_of_opcode : "NULL"));                  

            /* Handle param1 */
            if (param1_of_opcode)
            {
                param_number++;
                counter_tokens++;
                if (is_register_in_assembler(param1_of_opcode))
                {
                    param1_reg = true;
                    printf("DEBUG: param1 '%s' is a register\n", param1_of_opcode);
                }
                else
                {
                    (*IC)++;
                    printf("DEBUG: param1 '%s' is not a register => IC++ => %d\n", param1_of_opcode, *IC);
                }
            }

            /* Handle param2 */
            if (param2_of_opcode)
            {
                param_number++;
                counter_tokens++;

                if (is_register_in_assembler(param2_of_opcode) && param1_reg)
                {
                    param2_reg = true;
                    printf("DEBUG: param2 '%s' is a register + param1 was register => IC++ => %d\n", param2_of_opcode, *IC);
                }
                else 
                {
                    (*IC) += 1;
                    printf("DEBUG: param2 '%s' is NOT a register, but param1 was => IC += 2 => %d\n", param2_of_opcode, *IC);
                }
            }

            /* If label found, add or update its symbol entry */
            if (label_name[0] != '\0')
            {
                symbol* symbol_to_add = find_symbol(*symbol_table, label_name);
                if (symbol_to_add) /* symbol alredy exists. */
                {
                    printf("DEBUG: Updating existing symbol '%s' address to %d\n", label_name, IC_to_update);
                    /* Update the symbol's address and mark it as code */
                    symbol_to_add->address = IC_to_update;
                }
                else
                {
                    /* If the symbol doesn't exist, add it with address IC */
                    add_symbol(symbol_table, label_name, IC_to_update);
                    printf("DEBUG: Added new symbol '%s' at address %d\n", label_name, IC_to_update);
                }
            }
        }
        /*-------------------------------------------------*/
        /* .data / .string handling */
        /*-------------------------------------------------*/
        else if ((index = is_data(word)) != -1)
        {
            printf("DEBUG: Found data directive => '%s'\n", word);

            if (strcmp(instructions[index], ".data") == 0)
            {
                printf("new_buffer: %s\n", new_buffer);
                
                DC_to_update = handle_data_statement(new_buffer, cline, DC);
                if (DC_to_update == -1)
                {
                    return false;
                }

                new_symbol = find_symbol(*symbol_table, label_name);
                if (new_symbol)
                {
                    new_symbol->isData  = true;
                    new_symbol->address = DC_to_update;
                    printf("DEBUG: Updated symbol '%s' => address %d, isData=true\n", label_name, DC_to_update);
                }
                else if(label_name[0] != '\0')
                {
                    add_symbol(symbol_table, label_name, DC_to_update);
                    (find_symbol(*symbol_table, label_name))->isData = true;
                    printf("DEBUG: Added symbol '%s' => address %d, isData=true\n", label_name, DC_to_update);
                }
            }
            else if (strcmp(instructions[index], ".string") == 0)
            {
                symbol* new_symbol;
                int init_DC = handle_string_statement(new_buffer, cline, DC);
                if (init_DC == -1)
                    return false;

                printf("DEBUG: '.string' statement => updating DC to %d\n", *DC);

                new_symbol = find_symbol(*symbol_table, label_name);
                if (new_symbol)
                {
                    new_symbol->isData  = true;
                    new_symbol->address = init_DC;
                    printf("DEBUG: Updated symbol '%s' => address %d, isData=true\n", label_name, init_DC);
                }
                else if(label_name[0] != '\0')
                {
                    add_symbol(symbol_table, label_name, init_DC);
                    (find_symbol(*symbol_table, label_name))->isData = true;
                    printf("DEBUG: Added symbol '%s' => address %d, isData=true\n", label_name, init_DC);
                }
            }
        }
        /*-------------------------------------------------*/
        /* .entry / .extern handling */
        /*-------------------------------------------------*/
        if (strcmp(word, ".entry") == 0)
        {
            symbol* new_symbol;
            printf("DEBUG1: Found '.entry' directive\n");

            /* use line_copy for .entry handling */
            word = strtok(line_copy, " \t\n"); /* skip .entry? or label? */
            word = strtok(NULL,      " \t\n"); /* actual symbol after .entry */
            
            if (word)
            {
                word[strcspn(word, "\r\n")] = '\0'; /* remove newline */
                new_symbol = find_symbol(*symbol_table, word);
                if (new_symbol)
                {
                    new_symbol->isEnt = true;
                    printf("DEBUG2: Marking symbol '%s' as .entry\n", word);
                }
                else
                {
                    printf("enter\n");
                    /* If the symbol doesn't exist, we add it with address IC */
                    printf("word = **%s**\n", word);
                    add_symbol(symbol_table, word, *IC);
                    (find_symbol(*symbol_table, word))->isEnt = true;
                }
            }
        }
        if (strcmp(word, ".extern") == 0)
        {
            symbol* new_symbol;
            printf("DEBUG: Found '.extern' directive\n");

            word = strtok(NULL, " \t\n\r"); /* symbol after .extern */
            if (word)
            {
                word[strcspn(word, "\t\r\n")] = '\0'; /* remove newline */
                new_symbol = add_symbol(symbol_table, word, 0);
                new_symbol->isExt = true;
                printf("DEBUG: Added extern symbol '%s' => address 0, isExt=true\n", word);
            }
        }
    }
    else
    {
        /* DEBUG: The line does not contain a recognized command => no need to handle symbol */
        printf("DEBUG: Not a command => '%s'\n", (word ? word : "NULL"));
    }

    /* If we reach here, everything succeeded */
    return true;
}
