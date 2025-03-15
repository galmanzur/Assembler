#include "parser.h"



/*----------------------------------------------------------------------------*/
/*checking if character is in valid ascii table range from 0 to 127
getting a char c, return true if ASCII false if not*/
bool is_ascii(int c) 
{
	 return (c >= 0 && c <= 127); /*if char in ascii between 0 and 127*/
}

/*----------------------------------------------------------------------------*/
/*function to check if number is a whole number gets a str of number and cline
for error handling*/
bool is_whole_number(char *str)
{
    if (str == NULL)
    	return false;
    if(*str == '\0')
    	return false;

    /*check for sign - optional*/
    if (*str == '+' || *str == '-')
        str++;

    /*check if the remaining characters are digits*/
    while (*str != '\0')
    {
        if (!isdigit(*str))
        {
        	return false;
        }
        str++;
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/*checking if word is opcodes return index in list if it is else return -1*/
int is_opcode(char *word)
{
	int i;
	if(!word)
		return -1; 
    /*comparing if name is one conatianed in saved opcodes */
    for (i = 0; i < NUM_OPCODES; i++)
        if (strcmp(word, opcodes[i]) == 0) 
            return i;
    return -1;
}

/*----------------------------------------------------------------------------*/
/*checking if word is insruction return index in list if it is else return -1*/
int is_data(char *word)
{
	int i;
    /*check if the word is one contained in the saved instrictions*/
    for (i = 0; i < NUM_INSTRUCTIONS; i++) 
        if (strcmp(word, instructions[i]) == 0) 
            return i;
    return -1; 	
}

/*----------------------------------------------------------------------------*/
/*chekcing if word is opcode or instruction*/
bool is_command(char *word)
{
	return (is_opcode(word) != -1) || (is_data(word)  != -1);
}

/*----------------------------------------------------------------------------*/
/*function to check if word is computer register*/
bool is_register(char *word)
{
	int i;
	for (i = 0; i < NUM_REGISTERS; i++) 
    if (strcmp(word, registers[i]) == 0) 
        return true;
    return false;
}

/*----------------------------------------------------------------------------*/
/*function to check if the word is a safe word if it is return true
else if name is saved word in assembly language return false*/
bool is_safe_word(char *word)
{
	return (is_command(word) || is_register(word));
}

/*----------------------------------------------------------------------------*/
/*function to check if line is blank or comment line*/
bool blank_comment_line(char* line)
{
	char buffer[MAX_LINE], *word;
	strcpy(buffer, line);
	word = strtok(buffer, " \t\n");
	if(!word) 
		return true;
	if(word[0] == ';')
		return true; 
	return false;
}

/*----------------------------------------------------------------------------*/
/*checking if label is ended in : if it is return true else use cline for indicative 
error*/
bool check_label_colon(char *label)
{
    if (label) 
    {
        /*check if the label ends with a colon if not assumes not label*/
        if (strchr(label,':'))
            return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/*checking if str is of immediate addressing type */
bool immediate_addressing_check(char *str)
{
	return (str[0] == '#');
}

/*----------------------------------------------------------------------------*/
/*check if str is of type param_jump addressing*/
bool param_jump_check(char *str)
{
	str = strstr(str, "(");
	if(!str)
		return false;
	return true;
}

/*----------------------------------------------------------------------------*/
/*check if str is of type direct_register addressing return true or false depends*/
bool direct_register_check(char *str)
{
	return ((str[0] == 'r') && (strlen(str) == 2) && (isdigit(str[1])));
}

/*----------------------------------------------------------------------------*/
/*we assume the parameter we get is with no spacesget addressing type of str
using above functions*/
addressing check_addressing_type(char *str)
{
	if(!str)
		return -1;
	if(immediate_addressing_check(str))
		return immediate;
	if (direct_register_check(str))
		return direct_register;
	if (param_jump_check(str))
		return param_jump;
	return direct;
}

/*----------------------------------------------------------------------------*/
/*assuming opcode correct get line and check if starts with comma*/
bool start_with_coma(char *line, int cline)
{
	while(isspace(*line++));

	if (*line == ',')
	{
		printf("ERROR: comma before parameters in line %d\n", cline);
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------------*/
/*assuming opcode correct get line and check if ends with comma*/
bool end_with_coma(char *line, int cline)
{
	int i = strlen(line) - 1; 
	while (isspace(line[i]))
		i--;
	if (line[i] == ',')
	{
		printf("ERROR: comma at the end of line %d\n", cline);
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------------*/
/*function to count number of commas in line*/
int mutiple_comma(char* line)
{
	int i, counter_comma = 0;
	if(line == NULL)
		return -1;
	for (i = 0; line[i]; i++)
		if(line[i] == ',')
			counter_comma++;
	return counter_comma;
}
