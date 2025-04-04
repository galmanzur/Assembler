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
bool is_legal_number(char *str)
{
	printf("[is_legal_number]: is_legal_number called with str: %s\n", str);
    if (str == NULL)
    	return false;
    if(*str == '\0')
    	return false;

	if(str)
	{
		str = str + strspn(str, " \t\n\r"); /*skip spaces*/

		printf("[is_legal_number]: checking first char: %c\n", *str);	
		/*check for sign - optional*/
		if (*str == '+' || *str == '-')
			str++;
	
		/*check if the remaining characters are digits*/
		while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
		{
			printf("[is_legal_number]: checking char: %c\n", *str);
			if (!isdigit(*str))
			{
				printf("[is_legal_number]: is_legal_number returned false\n");
				return false;
			}
			str++;
		}
		printf("[is_legal_number]: is_legal_number returned true\n");
		
	}
	else
	{
		printf("[is_legal_number]: str is NULL\n");
		return false;
	}
	return true;
	
}

/*----------------------------------------------------------------------------*/
/*checking if word is opcodes return index in list if it is else return -1*/
int get_opcode(char *word)
{
	int i;
	if(!word)
		return -1; 
    /*comparing if name is one conatianed in saved opcodes */
    for (i = 0; i < NUM_OPCODES; i++)
        if (strcmp(word, opcodes[i].name) == 0) 
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
	return (get_opcode(word) != -1) || (is_data(word)  != -1);
}

/*----------------------------------------------------------------------------*/
/*function to check if word is computer register*/
bool is_register_in_assembler(char *word)
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
	return (is_command(word) || is_register_in_assembler(word));
}

/*----------------------------------------------------------------------------*/
/*function to check if line is blank or comment line*/
bool is_blank_or_comment(char* line)
{
	char buffer[MAX_LINE], *word;
	strcpy(buffer, line);
	word = strtok(buffer, " \t\n\r");
	if(!word) 
		return true;
	if(word[0] == ';')
		return true; 
	return false;
}

/*----------------------------------------------------------------------------*/
/*checking if label is ended in : if it is return true else use cline for indicative 
error*/
bool is_label_end_with_colon(char *label)
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
/*assuming opcode correct get line and check if starts with comma*/
bool is_start_with_coma(char *line, int cline)
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
bool is_end_with_coma(char *line, int cline)
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
int how_much_commas(char* line)
{
	int i, counter_comma = 0;
	if(line == NULL)
		return -1;
	for (i = 0; line[i]; i++)
		if(line[i] == ',')
			counter_comma++;
	return counter_comma;
}

bool is_label(char *word, int cline)
{
	int length;
	int i;
	if(word == NULL)
		return false;
	word = strtok(word, " \t\r\n"); /*skip spaces*/

    length = strlen(word); /*length of word*/

	if(!(length <= MAX_LABEL && word)) /*checking if label name is in range*/ 
	{
		printf("ERROR: Label '%s' at line %d is longer than %d characters. \n", word, cline, MAX_LABEL);
		return false;
	}	
	if (!isalpha(word[0])) /*checking first character in label name is alphabetical*/
	{
		printf("ERROR: The first character of label '%s' at line %d doesnt alphabetical. \n", word, cline);
		return false;
	}
	if(is_safe_word(word)) /*checking if word is safe*/		
	{
		printf("ERROR: Reserved word '%s' used in label at line %d\n", word, cline);
		return false;
	}
	for (i = 0; i < length; i++) /*checking if label name is in ascii range*/
	{
		if (!isalpha(word[i]) && !isdigit(word[i]))
		{
			printf("ERROR: Label '%s' at line %d contains invalid characters(alpha characters or digits). \n", word, cline);
			return false;
		}
	}
	return true;
}
/*----------------------------------------------------------------------------*/
/* this function checks if a line of assembly code is valid
 based on the format: opcode param1 , param 2
 there can be any number of spaces between opcode, params, and comma.*/
 bool valid_line_comma_spaces(char* line, int cline)
 {
	 char* ptr = line;
	 bool comma_flag = false;
 
	 while (*ptr != '\0') 
	 {
		 if (*ptr == ',') 
		 {
			 if (comma_flag == false)
			 {
				 printf("ERROR: invalid comma or spaces in line %d.\n", cline);
				 return false;
			 }
			 comma_flag = false;
		 } 
		 else if (isspace(*ptr)) 
		 {
			 /* Ignore multiple spaces */
			 while (isspace(*ptr))
				 ptr++;
			 /* If there's no comma after multiple spaces, set flag to false */
			 if (*ptr != ',' && *ptr != '\0')
				 comma_flag = false;
		 } 
		 else 
		 {
			 comma_flag = true;
		 }
		 ptr++;
	 }
	 return true;
 }

