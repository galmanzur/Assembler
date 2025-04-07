#include "encoding_service.h"

   
/*----------------------------------------------------------------------------*/
/*a function to handldle data encoding (numbers) in the second pass*/
void encode_instruction_data(char *param_line, int data_image[], int *DC)
{
    char* token = strtok(param_line, " ,\r\t\n");
    while(token)
    {
        data_image[(*DC)++] = atoi(token);
        token = strtok(NULL, " ,\r\t\n");
    }
}

/*----------------------------------------------------------------------------*/
/*another function to handle data encoding (string) in the second pass*/
void encode_instruction_string(char *param_line, int data_image[], int *DC)
{ 
    char* token = strtok(param_line, "\"");
    token = strtok(NULL, "\"");
    while(*token)
    {
        data_image[(*DC)++] = *token++;
    }
    data_image[(*DC)++] = 0; /*NULL terminator puting*/
}

/*----------------------------------------------------------------------------*/
/*function to encode parameters in code using a switch case*/
void encode_data_words(codeimage* current, symbol *symbol_table, char* param_source, char *param_dest, externList** extern_list, int IC)
{
    externList* new_external;
    /* Select the first defined parameter as the one to encode */
    char* param_to_encode = param_source ? param_source : param_dest;

    int addressing_type = identify_addressing_type(param_to_encode);

    /* Immediate, relative, and direct register encoded with A Flag (left to check if its direct addressing)*/
    int ARE = FLAG_ABSOLUTE;

    symbol* found_symbol = find_symbol(symbol_table, param_to_encode); 
    
    /* if source and destination are not defined, return 0. and  */
    int value_to_encode_if_exists = (param_to_encode) ? atoi(param_to_encode + 1) : 0;

    /* if symbol found - its mean direct or relative addressing, return address. If not found symbol its immediate/direct register addressing,
    so return the value of the number.*/
    int data_to_encode = (found_symbol) ? ( found_symbol->address) : value_to_encode_if_exists;

    switch(addressing_type)
    {
        case ADDRESSING_RELATIVE: 
            if (found_symbol)
            {
                /* Calculate the distance to the symbol */
                data_to_encode = found_symbol->address - (IC + current->number_of_words);

                /* In case relative to external */
                if (found_symbol->isExternal) 
                {
                    new_external = calloc(1, sizeof(externList));
                    strcpy(new_external->name, param_to_encode);
                    new_external->address = (IC + current->number_of_words);
                    new_external->next = *extern_list;
                    *extern_list = new_external;
                }
                else
                {
                    printf("[Addressing] data to encode: %d, cline: %d\n", data_to_encode, IC);    
                    load_data_word_to_code_image(current, ARE, data_to_encode);
                }
            }
            break;

        case ADDRESSING_DIRECT:
            if(found_symbol)
            {
                /* If the symbol is entry, set ARE to relocatable and if the symbol is external, set ARE to external */
                ARE = FLAG_RELOCATABLE;

                /* If the symbol is external, add it to the extern list */
                if(found_symbol->isExternal)
                {
                    ARE = FLAG_EXTERNAL;
                    new_external = calloc(1, sizeof(externList));
                    strcpy(new_external->name, param_to_encode);
                    new_external->address = (IC + current->number_of_words);
                    new_external->next = *extern_list;
                    *extern_list = new_external;
                }
                else
                {
                    printf("[Addressing] data to encode: %d, cline: %d\n", data_to_encode, IC);    
                    /* Load the distance from address of the symbol into the code image */
                    load_data_word_to_code_image(current, ARE, data_to_encode); 
                }
            }
            break;

            /* If the addressing type is immediate, load the data(number) directly into the code image */
        case ADDRESSING_IMMEDITAE:
            printf("[Addressing] data to encode: %d, cline: %d\n", data_to_encode, IC);    
            load_data_word_to_code_image(current, ARE, data_to_encode); 
            break;

            /* If direct register addressing, so I dont need to add anything to the code image */
        case ADDRESSING_DIRECT_REGISTER:    
            break;
    }
}

/*----------------------------------------------------------------------------*/
/*function to encode instruction lines of code and puting them in the codeimage*/
bool encode_command_line(codeimage** head, symbol *symbol_table, char* line, int *IC, externList** extern_list)
{
    int opcode_index;
    char* token;
    codeimage* current;
    char *source_param_str;
    char *dest_param_str = NULL;
    int source_addressing = 0;
    int dest_addressing = 0;
    int reg_source = 0;
    int reg_dest = 0;
    int funct;
    int params_required;
    int opcode_num;
    int ARE = FLAG_ABSOLUTE; /* value for ARE in command line*/

    /* Remove label from line if it exists */
    /* and check if the line is empty after removing the label */
    char* line_to_encode = remove_label(line);

    if(line_to_encode)
    {
        /* Gets the opcode and parameters from the line */
        token = strtok(line_to_encode, " \r\t\n");

        /* Gets opcode from list of opcodes */
        opcode_index = get_opcode(token);
        if (opcode_index == -1) 
        {
            printf("ERROR: %s is not a valid opcode.\n", token);
            return false;
        }
        
        current = insert_code(head);

        /* Gets data from opcode list */
        opcode_num = opcodes[opcode_index].opcode_num;
        params_required = opcodes[opcode_index].params_num;
        funct = opcodes[opcode_index].funct;
        
        printf("[Addressing] opcode: %s, funct: %d, opcode_num: %d, params_required: %d\n", token, funct, opcode_num, params_required);

        /* Handle opcode with 2 parameters */
        if (params_required == 2) 
        {
            source_param_str = strtok(NULL, " ,\r\t\n");
            dest_param_str = strtok(NULL, " ,\r\t\n");
            if (!source_param_str || !dest_param_str)
            {
                printf("ERROR: Missing operands for instruction with 2 operands.\n");
                return false;
            }

            source_addressing = identify_addressing_type(source_param_str);
            dest_addressing = identify_addressing_type(dest_param_str);

            if (source_addressing == ADDRESSING_DIRECT && !find_symbol(symbol_table, source_param_str)) 
            {
                printf("ERROR: Undefined label '%s'\n", source_param_str);
                return false;
            }
            if (dest_addressing == ADDRESSING_DIRECT && !find_symbol(symbol_table, dest_param_str)) {
                printf("ERROR: Undefined label '%s'\n", dest_param_str);
                return false;
            }
            reg_source = (source_addressing == ADDRESSING_DIRECT_REGISTER) ? atoi(source_param_str + 1) : 0;
            reg_dest = (dest_addressing == ADDRESSING_DIRECT_REGISTER) ? atoi(dest_param_str + 1) : 0;
        }

        /* Handle opcode with 1 parameter (always will be destination) */
        else if (params_required == 1) 
        {
            dest_param_str = strtok(NULL, " ,\r\t\n");
            if(!dest_param_str) 
            {
                printf("ERROR: Missing operand for instruction with 1 operand.\n");
                return false;
            }
            dest_addressing = identify_addressing_type(dest_param_str);
            source_addressing = 0; /* Just destination operand */

            if (dest_addressing == ADDRESSING_DIRECT && !find_symbol(symbol_table, dest_param_str)) {
                printf("ERROR: Undefined label '%s'\n", dest_param_str);
                return false;
            }
    
            reg_dest = (dest_addressing == ADDRESSING_DIRECT_REGISTER) ? atoi(dest_param_str + 1) : 0;
        }

        /* Handle opcode with 0 parameter (In my assembler, it's will be always rts / stop) */
        else if(params_required == 0) 
        {
            source_addressing = 0;
            dest_addressing = 0;
            reg_source = 0;
            reg_dest = 0;
        }
        else /* Invalid number of parameters - BUG !! */
        {
            printf("ERROR: Invalid number of parameters for opcode '%s'.\n", token);
            return false;
        }

        /* --------------------------Call encode: -------------------------*/
        /* Fill the first instruction word  */
        load_first_word_to_code_image(current, ARE, funct, reg_dest, dest_addressing, reg_source, source_addressing, opcode_num);

        /* ----- Fill parameter words ----- */
        if (params_required == 2) 
        {
            printf("[Addressing] source param: %s, dest param: %s\n", source_param_str, dest_param_str);
            encode_data_words(current, symbol_table, source_param_str, NULL, extern_list, *IC);
            printf("[Addressing] dest param: %s\n", dest_param_str);
            encode_data_words(current, symbol_table, NULL, dest_param_str, extern_list, *IC);
        } 
        else if (params_required == 1) 
        {
            printf("[Addressing] dest param: %s\n", dest_param_str);
            encode_data_words(current, symbol_table, NULL, dest_param_str, extern_list, *IC);
        }
            

        *IC += current->number_of_words;
    }
    
    return true;
}

/*----------------------------------------------------------------------------*/
/* Function to encode a line of assembly code. It handles labels, commands, and data.
 * It updates the instruction counter - IC and data counter -DC.
 * The function returns true if the line was successfully encoded, false otherwise.
 */
bool encode_line(codeimage** current, symbol **symbol_table, char* line, int* DC, int* IC, int data_image[], externList** extern_list)
{
    char *word, *token, buffer[MAX_LENGTH_LINE];
    directive_type index_directive_type;
    char param_of_directive_line[MAX_LENGTH_LINE];
    strcpy(buffer, line);

    word = strtok(line, " \r\t\n");

    if(!word) /*if word is NULL then line is empty*/
        return true;

    index_directive_type = get_directive_in_line(word); 
   
    if (is_label_end_with_colon(word)) /*0 because line is perfect*/
    {
        token = strchr(word, ':');
        *token = 0;
        token = (*(token + 1) != 0) ? token + 1 : NULL;
        word = strtok(token, " \r\t\n"); /*word is definetly a command*/
    }

    /* Check if assembly opcode in assembler*/
    if(get_opcode(word) != -1)
    {
        if(!encode_command_line(current, *symbol_table, buffer ,IC, extern_list))
            return false;
    }    

    else if(index_directive_type == DIRECTIVE_STRING || index_directive_type == DIRECTIVE_DATA ) /*because data and string are the first two in array*/
    {
        extract_params(buffer, param_of_directive_line);

            if(index_directive_type == DIRECTIVE_DATA)
                encode_instruction_data(param_of_directive_line, data_image, DC); 
   
            else if(index_directive_type == DIRECTIVE_STRING)
                encode_instruction_string(param_of_directive_line, data_image, DC);         
    }

    return true;
}

/*----------------------------------------------------------------------------*/
/*a function to handle and fill encoding for lables or parameters of immediate
addressing type*/
void load_data_word_to_code_image(codeimage* current, unsigned ARE, unsigned data)
{
    int size = current->number_of_words;

    current->encoded_instruction[size].data_word.ARE = ARE;
    current->encoded_instruction[size].data_word.data = data;  
    current->number_of_words++;
}

/*----------------------------------------------------------------------------*/
/*a function to fill word for the encoded IC word*/
void load_first_word_to_code_image(codeimage* current, unsigned ARE, unsigned funct, unsigned register_dest, unsigned addressing_dest, unsigned register_source, unsigned addressing_source, unsigned opcode)
    {
        int size = current->number_of_words;
        
        current->encoded_instruction[size].first.ARE = ARE;
        current->encoded_instruction[size].first.funct = funct; 
        current->encoded_instruction[size].first.register_dest = register_dest;
        current->encoded_instruction[size].first.addressing_dest = addressing_dest;
        current->encoded_instruction[size].first.register_source = register_source;
        current->encoded_instruction[size].first.addressing_source = addressing_source;
        current->encoded_instruction[size].first.opcode = opcode;        
        current->number_of_words++;
    }
