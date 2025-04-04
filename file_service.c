#include "file_service.h"


/*check if file exists with right permissions*/
bool is_file_readable(char* filename)
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

/*----------------------------------------------------------------------------*/
/*because the file name arguments are without assembly file .as extension
this function manipulates the name and adds the extension*/
char* add_extension(char* filename, char* extension)
{
    char* filename_with_extension;

    if (filename == NULL || extension == NULL) 
    {
        return NULL;
    }

    filename_with_extension = malloc(strlen(filename) + strlen(extension) + 1);
    /* copies file name without extension to new_filename variable */
    strcpy(filename_with_extension, filename);
    /* concatenates the extension to the file name.*/
    strcat(filename_with_extension, extension);

    return filename_with_extension; /*returning new desired name to be used*/
}