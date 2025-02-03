
#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <unistd.h>
#include <string.h>

/// @brief Writes a string to a file.
/// @param errors_list 
/// @param filename 
/// @param str 
void write_to_file(error_table *errors_list,char *filename, char *str);

/// @brief This function removes a file with the given filename.
/// @param filename (char*): A string representing the name of the file to remove.
void remove_file(char* filename);



#endif /* FILE_SERVICE_H */
