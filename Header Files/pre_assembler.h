#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

/// @brief 
typedef struct macro {
    char *name;
    char *content;
    int line;
    struct macro *next;
} macro;


/// @brief This function checks if a given token is the start of a macro declaration or not.
/// @param token (char*): A string representing the token to check.
/// @return returns 1 if the token is the start of a macro declaration, 0 otherwise
int is_macro_declaration(char *token);

/// @brief This function checks if a given token is the end of a macro declaration or not.
/// @param token (char*): A string representing the token to check.
/// @return returns 1 if the token is the end of a macro declaration, 0 otherwise
int is_macro_end(char *token);

//--------------------------------------------------------------------------------------------

/// @brief 
/// @param name 
/// @param line 
/// @return 
int add_macro(char *name,int line);


/// @brief 
/// @param macro_name 
/// @return 
macro *is_macro_name(char *macro_name);

/// @brief 
/// @param new_content 
/// @return 
int append_macro_content(char *new_content);

/// @brief 
/// @return 
macro *get_last_macro();

/// @brief  
void remove_last_macro();

/// @brief
void free_macros();


#endif
