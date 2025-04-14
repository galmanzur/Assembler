#include "addressing_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* Mapping of opcodes to their addressing types for each parameter. */
const opcode_and_addressing_for_each_param opcodes_table[NUMBER_OF_OPCODES] = {
    {&opcodes[0], DENY_ONLY_ADDRESSING_2, ALLOW_ADDRESSING_1_AND_3}, /* mov */
    {&opcodes[1], DENY_ONLY_ADDRESSING_2, DENY_ONLY_ADDRESSING_2}, /* cmp */
    {&opcodes[2], DENY_ONLY_ADDRESSING_2, ALLOW_ADDRESSING_1_AND_3}, /* add */
    {&opcodes[3], DENY_ONLY_ADDRESSING_2, ALLOW_ADDRESSING_1_AND_3}, /* sub */
    {&opcodes[4], ALLOW_ONLY_ADDRESSING_1, ALLOW_ADDRESSING_1_AND_3}, /* lea*/
    {&opcodes[5], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_3}, /* clr */
    {&opcodes[6], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_3}, /* not */
    {&opcodes[7], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_3}, /* inc */
    {&opcodes[8], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_3}, /* dec */
    {&opcodes[9], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_2}, /* jmp */
    {&opcodes[10], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_2}, /* bne */
    {&opcodes[11], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_2}, /* jsr */
    {&opcodes[12], NONE_ADDRESSING_ALLOW, ALLOW_ADDRESSING_1_AND_3}, /* red */
    {&opcodes[13], NONE_ADDRESSING_ALLOW, DENY_ONLY_ADDRESSING_2}, /* prn */
    {&opcodes[14], NONE_ADDRESSING_ALLOW, NONE_ADDRESSING_ALLOW}, /* rts */
    {&opcodes[15], NONE_ADDRESSING_ALLOW, NONE_ADDRESSING_ALLOW} /* stop */
};

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function gets str and current_line and checks immediate adressing validation
if valid returns true, else return false.*/
bool validate_immediate(char *str, int current_line)
{
    if(str)
        str[strcspn(str, "\r\n")] = '\0'; /*remove \r\n from str*/
	if(!is_legal_number(++str))
	{
        print_error(current_line, "Using invalid immediate addressing.");
		return false;
	}
	return true;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function gets str and current_line and checks direct register addressing validation 
If valid returns true, else returns false */
bool validate_direct_register(char *str, int current_line)
{
    int i;
    if(str)
    {
        str = strtok(str, " \t\n\r");
        for (i = 0; i < NUMBER_OF_REGISTERS; i++)
        {
            if (strcmp(str, registers[i]) == 0)            
                return true;
        }           
    }
    print_error(current_line, "Using invalid direct register addressing.");
    return false;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function gets str and current_line and checks relative adressing validation
if valid returns true, else return false.*/
bool validate_relative(char *str, int current_line)
{
    str++;
    if(str)
    {
        str = strtok(str, " \t\n\r"); /*skip spaces*/
        if(is_label(str, current_line))
        {
            return true;
        }        
    }
    return false;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/** This function checks if the addressing type is valid for the given opcode.
 * It returns true if the addressing type is valid, false otherwise.
 * It uses the mapper_addressing_types_and_options function to check the addressing type against the allowed options for this opcode.
 */
bool validate_addressing_of_opcode(char *opcode_str, int current_line, char *line)
{
	 /* Identify the type of addressing */
     addressing_type_of_opcode type = identify_addressing_type(opcode_str);
 
     /* Process the address based on its identified type using a switch statement */
     switch (type) 
     {
        case ADDRESSING_IMMEDITAE:
             return validate_immediate(opcode_str, current_line);

        case ADDRESSING_DIRECT:
             return is_label(opcode_str, current_line);

        case ADDRESSING_DIRECT_REGISTER:
             return validate_direct_register(opcode_str, current_line);

        case ADDRESSING_RELATIVE:
            return validate_relative(opcode_str, current_line);

        default:
             return false;
     }
}    

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function mapps addressing types to addressing options for a given opcode.
 * It checks if the addressing type is valid for the given opcode parameter (source or destination).
 * It returns true if the addressing type is valid, false otherwise.
 */
bool mapper_addressing_types_and_options(addressing_option_of_opcode addressing_option, addressing_type_of_opcode addressing_type)
{
	/*ook at opcode_table*/
	switch(addressing_option)
	{
		case NONE_ADDRESSING_ALLOW:
			break; /* assuming there is at least one parameter --> return false*/
		case ALLOW_ONLY_ADDRESSING_1:
			if(addressing_type == ADDRESSING_DIRECT)
				return true;
			break;
		case DENY_ONLY_ADDRESSING_2: 
			if (addressing_type != ADDRESSING_RELATIVE)
				return true;
			break;
		case ALLOW_ADDRESSING_1_AND_2:
			if ((addressing_type == ADDRESSING_DIRECT)||(addressing_type == ADDRESSING_RELATIVE))
				return true;
			break;
		case ALLOW_ADDRESSING_1_AND_3:
        if ((addressing_type == ADDRESSING_DIRECT)||(addressing_type == ADDRESSING_DIRECT_REGISTER))
				return true; 
			break;
	}
	return false;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the addressing type is valid for the given opcode parameter (source or destination).
 * It returns true if the addressing type is valid, false otherwise.
 * It uses the mapper_addressing_types_and_options function to check the addressing type against the allowed options for this opcode.
 */
bool validate_addressing_to_received_opcode_param(int index_opcode, char* word, int is_source_or_dest, int current_line)
{
    /* is_source_or_dest == 0 for source, 1 for destination */
    addressing_option_of_opcode addressing_option = (is_source_or_dest ? opcodes_table[index_opcode].destination : opcodes_table[index_opcode].source);
    
    /* Identify the type of addressing from the given word */
    addressing_type_of_opcode addressing_type = identify_addressing_type(word);

    /* Check if no parameters are expected, return true only if no addressing is required */
    if (opcodes[index_opcode].params_num == 0) 
    {
        return (addressing_option == NONE_ADDRESSING_ALLOW);
    }

    /* If there is exactly one parameter, always use the destination */
    if (opcodes[index_opcode].params_num == 1) 
    {
        addressing_option = opcodes_table[index_opcode].destination;
    }

    /* Validate if the recognized addressing type matches the allowed options for this opcode */
    if (!mapper_addressing_types_and_options(addressing_option, addressing_type)) 
    {
        /* Print an error message if there is a mismatch */
        print_error(current_line, "Invalid addressing type usage.");
        return false;
    }

    /* Return true if the addressing type is valid */
    return true;
}

/*---------------------------------------------Identify Functions 👀----------------------------------------------                                      */

/* This function identifies the addressing type of a given string.
 * It takes a string as input and returns the corresponding addressing type.
 * It uses the is_immediate_addressing, is_relative_addressing, and is_direct_register_addressing functions to identify the addressing type.
 */
addressing_type_of_opcode identify_addressing_type(char *str)
{
	if(!str)
		return -1;
	if(is_immediate_addressing(str))
		return ADDRESSING_IMMEDITAE;
	if (is_direct_register_addressing(str))
		return ADDRESSING_DIRECT_REGISTER;
	if (is_relative_addressing(str))
		return ADDRESSING_RELATIVE;
	return ADDRESSING_DIRECT;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the string is of type immediate addressing.
 * It returns true if the string is of type immediate addressing, false otherwise. */
bool is_immediate_addressing(char *str)
{
	return (str[0] == '#');
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the string is of type relative addressing.
 * It returns true if the string is of type relative addressing, false otherwise. */
bool is_relative_addressing(char *str)
{
	str = strstr(str, "&");
	if(!str)
		return false;
	return true;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the string is of type direct register addressing.
 * It returns true if the string is of type direct register addressing, false otherwise. */
/*check if str is of type direct_register addressing return true or false depends*/
bool is_direct_register_addressing(char *str)
{
	return ((str[0] == 'r') && (strlen(str) == 2) && (isdigit(str[1])));
}