#include "encoding_service.h"

/*----------------------------------------------------------------------------*/

/*function to check machine code overflow in computer memory 100 words of memory
are reserver hence machine code of IC + DC can only be 156 memory word*/
bool is_code_overflow(int IC, int DC)
{
	if((IC + DC) > USABLE_MEMORY_SIZE)
	{
		printf("ERROR: OVREFLOW! Machine code is greater then 256 memeory words\n");
		return false;
	}
	else
		return true;
}

/*----------------------------------------------------------------------------*/
/*a function to created new code image node of the struct for encoding*/
codeimage* new_code_image()
{
    codeimage* new = calloc(1, sizeof(codeimage));
    if(!new)
    {
        printf("CRITICAL: memory problem!\n");
        exit(EXIT_FAILURE);
    }
    new->L = 0;
    return new;
}


/*----------------------------------------------------------------------------*/
/*a function to handle and fill encoding for registers*/
void fill_register_word(codeimage* current,
                        unsigned dest, unsigned source)
{
    int L = current->L;
    /*because calloc inits ARE, we do no init ARE*/
    current->encoded_instruction[L].reg.dest = dest;
    current->encoded_instruction[L].reg.source = source;  
    current->L++;
}

/*----------------------------------------------------------------------------*/
/*a function to handle and fill encoding for lables or parameters of immediate
addressing type*/
void fill_label_or_immediate(codeimage* current, unsigned ARE, unsigned address)
{
    int L = current->L;
    /*because calloc inits ARE, we do no init ARE*/
    current->encoded_instruction[L].address.ARE = ARE;
    current->encoded_instruction[L].address.address = address;  
    current->L++;
}

/*----------------------------------------------------------------------------*/
/*a function to fill word for the encoded IC word*/
void fill_encoded_IC(codeimage* current, unsigned dest,
    unsigned source, unsigned opcode, unsigned register_dest, unsigned register_source)
    {
        int L = current->L;
        /*because calloc inits ARE, we do no init ARE*/
        current->encoded_instruction[L].first.dest = dest;
        current->encoded_instruction[L].first.source = source;
        current->encoded_instruction[L].first.opcode = opcode;
        current->encoded_instruction[L].first.register_dest = register_dest;
        current->encoded_instruction[L].first.register_source = register_source;
        current->L++;
    }
    
/*----------------------------------------------------------------------------*/
/*a function to handldle data encoding (numbers) in the second pass*/
void encode_data(char *param_line, int data_image[], int *DC)
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
void encode_string(char *param_line, int data_image[], int *DC)
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
void encode_parameter(codeimage* current, symbol *symbol_table, char* source,
                     char *dest, externList** extern_list, int IC)
{
    char* param = source?source:dest;
    int addressing_type = identify_addressing_type(param);
    int ARE = absolute;
    symbol* symbol_place = find_symbol(symbol_table, param); 
    int source_val = (source)?atoi(source + 1):0;
    int dest_val = (dest)?atoi(dest + 1):0;
    int address = (symbol_place)?(symbol_place->address):source_val;
    switch(addressing_type)
    {
        case relative: 
        case direct:
            if(symbol_place)
            {
                ARE = (symbol_place->isExt)?external:relocatable;
                if(address == 0)
                {
                    externList* new = calloc(1, sizeof(externList));
                    strcpy(new->name, param);
                    new->address = (IC + current->L);
                    new->next = *extern_list;
                    *extern_list = new;
                }
            }
        case immediate:
            fill_label_or_immediate(current, ARE, address); 
            break;
        case direct_register:
            fill_register_word(current, dest_val, source_val);
            break;
    }
}

/*----------------------------------------------------------------------------*/
/*function to insert code image node to code image linked list*/ 
codeimage* insert_code(codeimage** head)
{
    codeimage* new = new_code_image();
    codeimage* curr = *head;
    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        while(curr->next)
        {
            curr = curr->next;
        }
        curr->next = new;
    }
    return new;
}

/*----------------------------------------------------------------------------*/
/*function to destroy the code image after we done using it*/
void free_code_image(codeimage* head)
{
    while(head)
    {
        codeimage* temp = head;
        head = head->next;
        free(temp);
    }
}

/*----------------------------------------------------------------------------*/
/*function to destroy externalList after all extern labels are being written
to the .ext file*/
void free_external_list(externList* head)
{
    while(head)
    {
        externList* temp = head;
        head = head->next;
        free(temp);
    }
}



/*----------------------------------------------------------------------------*/
/*function to encode instruction lines of code and puting them in the codeimage*/
bool encode_instruction(codeimage** head, symbol *symbol_table, char* line,
                         int *IC, externList** extern_list)
{
    char* labeless_line = remove_label(line);
    if(labeless_line)
    {

        char* jump_check_ptr = strchr(labeless_line, '(');
        char* token = strtok(labeless_line, " \r\t\n");
        int opcode = get_opcode(token);
        int source_addressing, dest_addressing;
        int param1 = 0;
        int param2 = 0;
        char *param1_str = strtok(NULL," ,(\r\t\n");
        char *param3_str = NULL;
        char *param2_str = NULL;
        codeimage* current = insert_code(head);
        if(param1_str)
        {
            param2_str = strtok(NULL," ,\r\t\n");
            source_addressing = identify_addressing_type(param1_str);
            if(source_addressing == direct)
            {
                if(!find_symbol(symbol_table, param1_str))
                {
                    printf("ERROR: use of undefined label %s.\n", param1_str);
                    return false;
                }
            }
            dest_addressing = identify_addressing_type(param2_str);
            if(dest_addressing == direct)
            {
                if(!find_symbol(symbol_table, param2_str))
                {
                    printf("ERROR: use of undefined label %s.\n", param2_str);
                    return false;
                }
            }

            if(jump_check_ptr)
            {
                param3_str = strtok(NULL, " ,)\r\t\n");
                param1 = dest_addressing;
                dest_addressing = relative;
                source_addressing = immediate;
                param2 = identify_addressing_type(param3_str);
                if(param2 == direct)
                {
                    if(!find_symbol(symbol_table, param3_str))
                    {
                        printf("ERROR: use of undefined label %s.\n", param3_str);
                        return false;
                    }
                }
            }

            if(dest_addressing == -1)
            {
                dest_addressing = source_addressing;
                source_addressing = 0; /*no param1 and 2*/
            }
        }

        fill_encoded_IC(current,dest_addressing,source_addressing,opcode,param2,param1);
        if(param1_str)
        {
            if(source_addressing == direct_register && dest_addressing == direct_register)
            {
                encode_parameter(current, symbol_table, param1_str, param2_str, extern_list, *IC);
                (*IC) += current->L;
                return true;
            }
            encode_parameter(current, symbol_table, param1_str, param2_str, extern_list, *IC);
        }
        if(param2_str)
        {
            if(param1 == direct_register && param2 == direct_register)
            {
                encode_parameter(current, symbol_table, param2_str, param3_str, extern_list, *IC);
                (*IC) += current->L;
                return true;
            }
            encode_parameter(current, symbol_table, param2_str, param3_str, extern_list, *IC);
        }
        if(param3_str)
        {
            encode_parameter(current, symbol_table, NULL, param3_str, extern_list, *IC);
        }
        (*IC) += current->L;
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/*functiong to simplify use of all other functions and is used as the main
function to encode line of code*/
bool encode(codeimage** current, symbol **symbol_table, char* line, int* DC, int* IC,
             int data_image[], externList** extern_list)
{
    char *word, *token, buffer[MAX_LINE];
    strcpy(buffer, line);
    /*label handling only if lable exists*/
    word = strtok(line, " \r\t\n");
    if(!word) /*if word is NULL then line is empty*/
        return true;
    if (is_label_end_with_colon(word)) /*0 because line is perfect*/
    {
        token = strchr(word, ':');
        *token = 0;
        token = (*(token + 1) != 0)?token + 1:NULL;
    }
    if(get_opcode(word) != -1)
    {
        if(!encode_instruction(current, *symbol_table, buffer ,IC, extern_list))
            return false;
    }

    else if(is_data(word) == 0 || is_data(word) == 1 ) /*because data and string are the first two in array*/
    {
        char param_line[MAX_LINE];
        extract_params(buffer, param_line);
        if(is_data(word) == 0)
            encode_data(param_line, data_image, DC); 
        if(is_data(word) == 1)
            encode_string(param_line, data_image, DC);

    }
    return true;
}
