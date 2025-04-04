#include "second_pass.h"
#include "symbol_repo.h"

/*----------------------------------------------------------------------------*/
/*function that used the above function, encodes and validates the code if
all validation passed in first and second pass*/
bool second_pass(char* filename, codeimage** current, symbol **symbol_table,
    int* DC, int* IC, int data_image[], externList** extern_list)
{
int cline = 0;
bool is_valid = true;
char* original_name = add_extension(filename, ".am");
char buffer[MAX_LINE], buffer_copy[MAX_LINE];
FILE* origin_ptr;
if(!check_file(original_name))
return false;
origin_ptr = fopen(original_name, "r");
(*IC) = 100;
(*DC) = 0;

while(fgets(buffer, MAX_LINE, origin_ptr))
{
cline++;
strcpy(buffer_copy, buffer);
if (blank_comment_line(buffer))
continue;
else
{   
if(!encode(current, symbol_table, buffer_copy, DC, IC, data_image, extern_list))
   is_valid = false;          
}
}
if(is_valid)
{
write_entry(*symbol_table, filename);
write_object(filename, *current, *DC, *IC, data_image);
write_extern(*extern_list, filename);
}
free(original_name);
fclose(origin_ptr);
return true;
}

/*----------------------------------------------------------------------------*/
/*function to destroy externalList after all extern labels are being written
to the .ext file*/
void destroy_externlist(externList* head)
{
    while(head)
    {
        externList* temp = head;
        head = head->next;
        free(temp);
    }
}

/*----------------------------------------------------------------------------*/
/*a function to take full line of code and retur it without the lable in the 
beginning if label is present, else returns line as is.*/
char* create_labeless_line(char* line)
{
    char* ptr = strchr(line, ':');
    if(ptr)
        return (ptr + 1);
    while(isspace(*line))
        line++;
    return line;
}

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