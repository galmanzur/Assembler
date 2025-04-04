#include "addressing_service.h"

const opcode_and_addressing_for_each_param opcodes_table[NUM_OPCODES] = {
    {&opcodes[0], DENY_ONLY_2, ALLOW_1_AND_3}, /* mov */
    {&opcodes[1], DENY_ONLY_2, DENY_ONLY_2}, /* cmp */
    {&opcodes[2], DENY_ONLY_2, ALLOW_1_AND_3}, /* add */
    {&opcodes[3], DENY_ONLY_2, ALLOW_1_AND_3}, /* sub */
    {&opcodes[4], ALLOW_ONLY_1, ALLOW_1_AND_3}, /* lea*/
    {&opcodes[5], NONE, ALLOW_1_AND_3}, /* clr */
    {&opcodes[6], NONE, ALLOW_1_AND_3}, /* not */
    {&opcodes[7], NONE, ALLOW_1_AND_3}, /* inc */
    {&opcodes[8], NONE, ALLOW_1_AND_3}, /* dec */
    {&opcodes[9], NONE, ALLOW_1_AND_2}, /* jmp */
    {&opcodes[10], NONE, ALLOW_1_AND_2}, /* bne */
    {&opcodes[11], NONE, ALLOW_1_AND_2}, /* jsr */
    {&opcodes[12], NONE, ALLOW_1_AND_3}, /* red */
    {&opcodes[13], NONE, DENY_ONLY_2}, /* prn */
    {&opcodes[14], NONE, NONE}, /* rts */
    {&opcodes[15], NONE, NONE} /* stop */
};

/*----------------------------------------------------------------------------*/

/*getting str and cline and checks immediate adressing validation
if valid returns true, else return false + indicative error message*/
bool validate_immediate(char *str, int cline)
{
    if(str)
        str[strcspn(str, "\r\n")] = '\0'; /*remove \r\n from str*/
    printf("[validate_immediate********]: validate_immediate called with str: %s, cline: %d\n", str, cline);
	if(!is_legal_number(++str))
	{
		printf("ERROR: %s using invalid immediate addressing in line %d.\n", str, cline);
		return false;
	}
	return true;
}

/*----------------------------------------------------------------------------*/

/*getting str and cline and checks direcr register adressing validation
if valid returns true, else return false + indicative error message*/
bool validate_direct_register(char *str, int cline)
{
	int num = atoi(str+1);
	if(!((0 <= num) && (num <= 7)))
	{
		printf("ERROR: %s is invalid direct register addressing in line %d.\n", str, cline);
		return false;
	}
	return true;
}

/*----------------------------------------------------------------------------*/

 /*function to get str and cline to check if all addressing is valid
 except for addressing type number 2*/
bool validate_except_paramjump(char *str, int cline)
{
	 /* Identify the type of addressing */
     addressing_types type = identify_addressing_type(str);

     /* Check if the type is 'param_jump', which should not be handled by this function */
     if (type == param_jump) {
         return false;
     }
 
     /* Process the address based on its identified type using a switch statement */
     switch (type) 
     {
         case immediate:
             return validate_immediate(str, cline);

         case direct:
             return is_safe_label(str, cline);

             case direct_register:
             return validate_direct_register(str, cline);

         default:
             return false;
     }
}

/*----------------------------------------------------------------------------*/

/*checking for unnecessary spaces inside param jump*/
bool has_pjump_spaces(char* str, int cline)
{
	while(*str != 0)
	{
		if(isspace(*str++))
		{
			printf("ERROR: invalid spaces in param jump addressing in line %d.\n", cline);
			return true;
		}
	}
	return false;
}

/*----------------------------------------------------------------------------*/

/*assuming all spaces and ',' are validating param_jump addressing type
with cline for indicative error*/
bool validate_param_jump(char *line, int cline)
{
	int i = 0;
	/*for ease of use delim is in array*/
	char *delim[3] = {"(", ",", ")"};
	char buffer[MAX_LINE], *token;
	strcpy(buffer, line);
	while(isspace(buffer[i]))
		i++; /*label without spaces*/
	token = strtok(buffer + i, delim[0]);
	if(is_safe_label(token, cline) || !has_pjump_spaces(token, cline))
	{
		for (i = 1; i < 3; i++)
		{
			token = strtok(NULL, delim[i]);
			if(!token)
				return false;
			if(has_pjump_spaces(token, cline))
				return false;
			if(!validate_except_paramjump(token, cline))
				return false;
		}
	}
	else
		return false;
	return true;
}

/*----------------------------------------------------------------------------*/

/*checks if addressing is written correctly*/
bool validate_addressing(char *str, int cline, char *line)
{
	return (identify_addressing_type(str) != param_jump)?
		validate_except_paramjump(str,cline):
		validate_param_jump(line,cline);	
}    

/*----------------------------------------------------------------------------*/

/*function with switch case getting addressing status and 
addressing type and handel accordingly - will be used in validate addressing
type*/
bool is_addressing_types_and_options_matching(addressing_options addressing_option, addressing_types addressing_type)
{
	/*only case look at opcode_table*/
	switch(addressing_option)
	{
		case NONE:
			break; /* assuming there is at least one parameter --> return false*/
		case ALLOW_ONLY_1:
			if(addressing_type == direct)
				return true;
			break;
		case DENY_ONLY_2: 
			if (addressing_type != param_jump)
				return true;
			break;
		case ALLOW_1_AND_2:
			if ((addressing_type == direct)||(addressing_type == param_jump))
				return true;
			break;
		case ALLOW_1_AND_3:
        if ((addressing_type == direct)||(addressing_type == direct_register))
				return true; 
			break;
	}
	return false;
}

/*----------------------------------------------------------------------------*/

/* Definitions of enums and structs should be included here or in a header file. */
/* This function validates the addressing type for a given opcode parameter (source or destination) */
bool validate_addressing_type(int index, char* word, int src_or_dst, int cline)
{
    /* Choose the addressing option based on the src_or_dst flag */
    /* src_or_dst == 0 for source, 1 for destination */
    addressing_options addressing_option = (src_or_dst ? 
                                            opcodes_table[index].destination : 
                                            opcodes_table[index].source);
    
    /* Identify the type of addressing from the given word */
    addressing_types addressing_type = identify_addressing_type(word);
    printf("Addressing recognized! addressing_typw: %d ,in line %d.\n", addressing_type, cline);
    /* Check if no parameters are expected, return true only if no addressing is required */
    if (opcodes[index].params_num == 0) {
        return (addressing_option == NONE);
    }

    /* If there is exactly one parameter, always use the destination addressing regardless of src_or_dst */
    if (opcodes[index].params_num == 1) {
        addressing_option = opcodes_table[index].destination;
    }

    /* Validate if the recognized addressing type matches the allowed options for this opcode */
    if (!is_addressing_types_and_options_matching(addressing_option, addressing_type)) {
        /* Print an error message if there is a mismatch */
        printf("ERROR: Invalid addressing type usage in line %d.\n", cline);
        return false;
    }

    /* Return true if the addressing type is valid */
    return true;
}

/* 
Functions - Recognizes the addressing type of a string.
*/

/*----------------------------------------------------------------------------*/
/*we assume the parameter we get is with no spacesget addressing type of str
using above functions*/
addressing_types identify_addressing_type(char *str)
{
	if(!str)
		return -1;
	if(is_immediate_addressing(str))
		return immediate;
	if (is_direct_register(str))
		return direct_register;
	if (is_param_of_jump(str))
		return param_jump;
	return direct;
}

/*----------------------------------------------------------------------------*/
/*checking if str is of immediate addressing type */
bool is_immediate_addressing(char *str)
{
	return (str[0] == '#');
}

/*----------------------------------------------------------------------------*/
/*check if str is of type param_jump addressing*/
bool is_param_of_jump(char *str)
{
	str = strstr(str, "(");
	if(!str)
		return false;
	return true;
}

/*----------------------------------------------------------------------------*/
/*check if str is of type direct_register addressing return true or false depends*/
bool is_direct_register(char *str)
{
	return ((str[0] == 'r') && (strlen(str) == 2) && (isdigit(str[1])));
}