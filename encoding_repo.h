/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                               **  Encoding Repo 📦 **
* This file contains the functions for basic operations on the code image linked list and extern list.
* It includes functions to create, insert, and free code image nodes.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef ENCODING_REPO_H
#define ENCODING_REPO_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "encoding_data.h"
#include "encoding_service.h"
#include "manager.h"
#include "enable_bool.h"
#include "print_to_console_service.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function checks if the code image has overflowed in memory.
 * It takes the instruction counter (IC) and data counter (DC) as parameters.
 * It returns true if there is an overflow, false otherwise. */
bool is_code_overflow(int IC, int DC);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function creates a new code image node for encoding. It returns a pointer to the newly created code image node. */
codeimage* create_code_image();

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function inserts a new code image node into the code image linked list.
 * It takes a pointer to the head of the linked list as a parameter and returns a pointer to the newly inserted code image node. */
codeimage* insert_code(codeimage** head);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the code image linked list.
 * It takes a pointer to the head of the linked list as a parameter. */
void free_code_image(codeimage* head);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function frees the memory allocated for the extern list.
 * It takes a pointer to the head of the extern list as a parameter. */
void free_extern_list(externList* head);

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* ENCODING_REPO_H */