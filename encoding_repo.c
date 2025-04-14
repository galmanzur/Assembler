#include "encoding_repo.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the code image has overflowed in memory.
 * It takes the instruction counter (IC) and data counter (DC) as parameters.
 * It returns true if there is an overflow, false otherwise. */
bool is_code_overflow(int IC, int DC)
{
	if((IC + DC) > ASSEMBLER_MEMORY_SIZE)
	{
		print_global_error("Code image overflow in memory!");
		return false;
	}
	else
		return true;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates a new code image node for encoding. It returns a pointer to the newly created code image node. */
codeimage* create_code_image()
{
    /* Allocate memory for the new code image node */
    codeimage* new = calloc(1, sizeof(codeimage));
    if(!new)
    {
        print_global_error("In allocate memory.");
        exit(EXIT_FAILURE);
    }
    /* Initialize the new words - number of instructions in the code image*/
    new->number_of_words = 0;
    return new;
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function inserts a new code image node into the code image linked list.
 * It takes a pointer to the head of the linked list as a parameter and returns a pointer to the newly inserted code image node. */
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

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the code image linked list.
 * It takes a pointer to the head of the linked list as a parameter. */
void free_code_image(codeimage* head)
{
    while(head)
    {
        codeimage* temp = head;
        head = head->next;
        free(temp);
    }
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the extern list.
 * It takes a pointer to the head of the extern list as a parameter. */
void free_extern_list(externList* head)
{
    while(head)
    {
        externList* temp = head;
        head = head->next;
        free(temp);
    }
}