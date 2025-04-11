#include "parser.h"

/* This function checks if a character is an ASCII character.
 * It takes an integer as a parameter and returns true if the character is ASCII, false otherwise. */
bool is_ascii(int number) 
{
	 return (number >= ASCII_MIN && number <= ASCII_MAX); /*if char in ascii between 0 and 127*/
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a number is a legal number.
    Legal number is one of the following: X, +X, -X. (In order the instructions. )
    It takes a string as a parameter and returns true if the number is legal, false otherwise. */
bool is_legal_number(char *number_str)
{
	/* Null check */
    if (number_str == NULL)
    	return false;

	/*check if the string is empty*/	
    if(*number_str == '\0')
    	return false;

	number_str = number_str + strspn(number_str, " \t\n\r"); /*skip spaces*/

	/* +X, -X, is legal*/
	if (*number_str == '+' || *number_str == '-')
		number_str++;

	/* Check if the remain characters are digits - Loop through the string until we reach the end or a space character */
	while (*number_str != '\0' && *number_str != ' ' && *number_str != '\t' && *number_str != '\n' && *number_str != '\r')
	{
		if (!isdigit(*number_str))
			return false; /*if not digit return false*/
		number_str++;
	}
		
	return true;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is an opcode.
 It takes a string as a parameter and returns the index of the opcode in the opcode list if it is valid, -1 otherwise. */
int get_opcode(char *opcode_str)
{
	int i;
	if(!opcode_str)
		return -1; 
    /*comparing if name is one conatianed in saved opcodes */
    for (i = 0; i < NUMBER_OF_OPCODES; i++)
        if (strcmp(opcode_str, opcodes[i].name) == 0) 
            return i;
    return -1;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a directive.
 It takes a string as a parameter and returns the index of the directive in the directive list if it is valid, -1 otherwise. */
directive_type get_directive_in_line(char *directive_str)
{
	int i;

    for (i = 0; i < NUMBER_OF_DIRECTIVES; i++) 
        if (strcmp(directive_str, directives_str[i]) == 0) 
            return i;
    return -1; 	
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a command.
 It takes a string as a parameter and returns true if the string is a command, false otherwise. */
bool is_command(char *command_str)
{
	return (get_opcode(command_str) != -1) || (get_directive_in_line(command_str)  != -1);
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a string is a register in the assembler.
 It takes a string as a parameter and returns true if the string is a register, false otherwise. */
bool is_register_in_assembler(char *register_str)
{
	int i;
	/*comparing if name is one of the saved registers */
	for (i = 0; i < NUMBER_OF_REGISTERS; i++) 
		if (strcmp(register_str, registers[i]) == 0) 
			return true;
	return false;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a word is a safe word.
 It takes a string as a parameter and returns true if the word is a safe (already exists in assmembler syntex) word, false otherwise. */
bool is_safe_word(char *word)
{
	return (is_command(word) || is_register_in_assembler(word));
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a line is blank or a comment.
 It takes a string as a parameter and returns true if the line is blank or a comment, false otherwise. */
bool is_blank_or_comment(char* line)
{
	char buffer[MAX_LENGTH_LINE], *word;
	strcpy(buffer, line);
	word = strtok(buffer, " \t\n\r");
	if(!word) 
		return true;
	if(word[0] == ';')
		return true; 
	return false;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a label ends with a colon.
 It takes a string as a parameter and returns true if the label ends with a colon, false otherwise. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/


/* This function checks if a string is a label.
 It takes a string and the current line number as parameters and returns true if the string is a label, false otherwise. */
bool is_label(char *label_str, int current_line)
{
	int length, i;
	label_str = strtok(label_str, " \t\r\n"); /*skip spaces*/

	if(!label_str) 
		return false;

    length = strlen(label_str); /*length of label_str*/

	if(length == 0) /*if label_str is empty*/
		return false;

	if(length > MAX_LENGTH_LABEL) /*checking if label name is in range*/ 
	{
		print_error(current_line, "Label name is too long.");
		return false;
	}	
	if (!isalpha(label_str[0])) /*checking first character in label name is alphabetical*/
	{
		print_error(current_line, "Label name must start with an alphabetical character.");
		return false;
	}
	if(is_safe_word(label_str)) /*checking if word safe*/		
	{
		print_error(current_line, "Label name is a reserved word.");
		return false;
	}
	for (i = 0; i < length; i++) /*checking if label name is in ascii range*/
	{
		if (!isalpha(label_str[i]) && !isdigit(label_str[i]))
		{
			print_error(current_line, "Label name contains invalid characters.");
			return false;
		}
	}
	return true;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if a line is valid based on the format: opcode param1 , param 2
 It takes a string and the current line number as parameters.*/
 bool valid_line_comma_spaces(char* line, int current_line)
 {
	 char* ptr = line;
	 bool comma_flag = false;
 
	 while (*ptr != '\0') 
	 {
		 if (*ptr == ',') 
		 {
			 if (comma_flag == false)
			 {
				 print_error(current_line, "Invalid comma placement in line.");
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

