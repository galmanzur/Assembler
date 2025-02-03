#ifndef SYMBOL_SERVICE_H
#define SYMBOL_SERVICE_H

/* Declarations for functions, types, and constants used by the symbol table module */
#define MAX_MEMORY_USAGE 256 /* instructions are that the hole program will no longer take space of 256 words in memory */
#define MAX_ADDRESS_SIZE 3

/* Define a struct for a symbol */
typedef struct {
    char *type;
    char *name;
    char *address;
    char *data;
} symbol;

/* Define a struct for a symbol table */
typedef struct {
    symbol **symbols;
    int num_symbols;
    int capacity;
} symbol_table;

/// @brief Initializes a symbol table by allocating memory for its symbols array and setting initial values for its properties.
/// @param table 
/// @return 
int init_symbol_table(symbol_table *table);

/// @brief Adds a symbol to a symbol table by creating a new symbol struct and inserting it into the symbols array.
/// @param table 
/// @param type 
/// @param name 
/// @param address 
/// @param data 
void add_symbol(symbol_table *table, char *type, char *name, char *address, char *data); 

/// @brief Checks if a symbol exists in a symbol table with the given name and type.
/// @param table 
/// @param type 
/// @param name 
/// @return 
int is_symbol(symbol_table *table,char *type ,char *name);

/// @brief Sets the data associated with a label in a symbol table to a new value.
/// @param table 
/// @param label_name 
/// @param label_data 
void set_label_data(symbol_table *table, char *label_name, char *label_data);

/// @brief Gets the address associated with a symbol in a symbol table.
/// @param table 
/// @param name 
/// @return 
char* get_symbol_address(symbol_table *table, char *name);

/// @brief Sets the address associated with a symbol in a symbol table to a new value.
/// @param table 
/// @param name 
/// @param new_address 
void set_symbol_address(symbol_table *table, char *name,char *new_address);

/// @brief Gets the data associated with a symbol in a symbol table.
/// @param table 
/// @param name 
/// @return 
char* get_symbol_data(symbol_table *table, char *name);

/// @brief Adds a value to the IC symbol in a symbol table.
/// @param table 
/// @param x 
void add_ic(symbol_table *table,int x); 

/// @brief Adds a value to the DC symbol in a symbol table.
/// @param table 
/// @param x 
void add_dc(symbol_table *table,int x);

/// @brief Gets the name of the last label in a symbol table.
/// @param table 
/// @return 
char *get_last_label(symbol_table *table);

/// @brief Updates the addresses of data and string symbols in a symbol table based on the value of the IC symbol.
/// @param table 
void update_addresses(symbol_table *table);

/// @brief Updates the data field of a label symbol in a symbol table.
/// @param table 
/// @param data 
/// @param new_str 
void get_label_data(symbol_table *table, char *data, char *new_str);

/// @brief helping method for Debugg - Prints the contents of a symbol table to stdout.
/// @param table 
void print_symbol_table(symbol_table *table); 

/// @brief Frees the memory used by a symbol table.
/// @param table 
void free_symbol_table(symbol_table *table); 


#endif /* SYMBOL_SERVICE_H */
