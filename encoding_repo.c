#include "encoding_repo.h"

/*----------------------------------------------------------------------------*/

/*function to check machine code overflow in computer memory 100 words of memory
are reserver hence machine code of IC + DC can only be 156 memory word*/
bool is_code_overflow(int IC, int DC)
{
	if((IC + DC) > ASSEMBLER_MEMORY_SIZE)
	{
		printf("ERROR: OVREFLOW! Machine code is greater then 256 memeory words\n");
		return false;
	}
	else
		return true;
}

/*----------------------------------------------------------------------------*/
/*a function to created new code image node of the struct for encoding*/
codeimage* create_code_image()
{
    /* Allocate memory for the new code image node */
    codeimage* new = calloc(1, sizeof(codeimage));
    if(!new)
    {
        printf("CRITICAL: memory problem!\n");
        exit(EXIT_FAILURE);
    }
    /* Initialize the new words - number of instructions in the code image*/
    new->number_of_words = 0;
    return new;
}

/*----------------------------------------------------------------------------*/
/*function to insert code image node to code image linked list*/ 
codeimage* insert_code(codeimage** head)
{
    codeimage* new = create_code_image();
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
void free_extern_list(externList* head)
{
    while(head)
    {
        externList* temp = head;
        head = head->next;
        free(temp);
    }
}