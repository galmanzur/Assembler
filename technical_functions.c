#include "technical_functions.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function extracts the parameters from a line of code and stores them in a new buffer.
* It takes the original line, the current line number, and the new buffer as parameters. */
void extract_params(char buffer[], char new_buffer[])
 {
	char *token, index;
	strcpy(new_buffer, buffer);
	token = strtok(new_buffer," \r\t\n");
	if(new_buffer[strlen(new_buffer)-1] == ':')
		token = strtok(NULL, " \r\t\n"); /*token is on opcode*/
	token = token + strlen(token); /*params*/
	index = token - new_buffer;
	strcpy(new_buffer, buffer + index);
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function removes the label from a line of code if present.
* It takes the line as a parameter and returns the line without the label. */
char* remove_label(char* line)
{
    char* ptr = strchr(line, ':');
    if(ptr)
        return (ptr + 1);
    while(isspace(*line))
        line++;
    return line;
}