/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                                ** Enable Bool ✔️🚫 **
This header file defines a boolean type and its values for use in the assembler.      
It is used to represent true and false values in the code.
This allows for better readability and maintainability of the code.                               
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef ENABLE_BOOL_H
#define ENABLE_BOOL_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This enum defines the boolean values used in the assembler. */
typedef enum {false, true} bool;

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* ENABLE_BOOL_H */