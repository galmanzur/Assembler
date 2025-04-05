#include "technical_functions.h"

/*assuming line is not destroyed
void copy_param_line(char buffer[], char new_buffer[])
{
	char *token, index;
	strcpy(new_buffer, buffer);
	token = strtok(new_buffer," \t\n");
	if(new_buffer[strlen(new_buffer)-1] == ':')
		token = strtok(NULL, " \t\n"); 
	token = token + strlen(token); 
	index = token - new_buffer;
	strcpy(new_buffer, buffer + index);
}*/
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


/*function that get index and return the number of parameters
int param_number(int index)
{
	int counter = 0;
	if(opcodes_table[index].source != NONE)
		counter++;
	if(opcodes_table[index].destination != NONE)
		counter++;
	return counter;
}*/