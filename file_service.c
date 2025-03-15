#include "file_service.h"

/*----------------------------------------------------------------------------*/
/*check if file exists with right permissions*/
bool check_file(char* filename)
{
    FILE* file = fopen(filename, "r");
    if(!file)
    {
        printf("CRITICAL:%s cannot be opened.\n", filename);
        return false;
    }
    fclose(file); /*closing if succeeded*/
    return true;
}


/*because the file name arguments are without assembly file .as extension
this function manipulates the name and adds the extension*/
char* add_extension(char* filename, char* extension)
{
    /* allocating memory for the file name with the extension */
    char* new_filename = malloc(strlen(filename) + strlen(extension) + 1);
    
    /* copies file name without extension to new_filename variable */
    strcpy(new_filename, filename);
    
    /* using stracat to concatenates the 2 strings to the new_filename
    resulting in the full file name with the extention*/
    strcat(new_filename, extension);
    
    return new_filename; /*returning new desired name to be used*/
    free(new_filename);
}