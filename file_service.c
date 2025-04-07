#include "file_service.h"



char *extension_file_source = ".as";
char *extension_file_after_preassembler = ".am";
char *fentry = ".ent";
char *fextern = ".ext";
char *fobject = ".ob";

/*check if file exists with right permissions*/
bool is_file_readable(char* filename)
{
    FILE* file_to_read = fopen(filename, "r");
    if(!file_to_read)
    {
        print_global_error("File can not be opened.");
        return false;
    }
    fclose(file_to_read); /*closing if succeeded*/
    return true;
}

/*----------------------------------------------------------------------------*/
/*because the file name arguments are without assembly file .as extension
this function manipulates the name and adds the extension*/
char* add_extenstion_to_file(char* filename, char* extension)
{
    char* filename_with_extension;

    if (filename == NULL || extension == NULL) 
    {
        return NULL;
    }

    filename_with_extension = malloc(strlen(filename) + strlen(extension) + 1);

    /* Copy the file name to the new string */
    strcpy(filename_with_extension, filename);

    /* Concatenate the extension to the file name */
    strcat(filename_with_extension, extension);

    /* Returns the new file name with the extension.*/
    return filename_with_extension; 
}

/*----------------------------------------------------------------------------*/
/*function that writes to file all labels which are entry lables with their 
coresponding IC address to the .ent file*/
void create_entry_file(symbol* head, char* filename) 
{
	char* entry_name = add_extenstion_to_file(filename, fentry);
	FILE* file = NULL;
    while (head != NULL) 
    {
        if ((head->isEntry) == true )
        {
            if(!file)
                file = fopen(entry_name, "w");
            fprintf(file, "%s\t%d\n", head->name, head->address);
        }
        head = head->next;
    }
    if(file)
        fclose(file);
    free(entry_name);
}

/*----------------------------------------------------------------------------*/
/*function to write to write all extern labels in file with coresponding IC 
of the lines they were used in*/
void create_extern_file(externList* head, char* filename) 
{
	char* extern_name = add_extenstion_to_file(filename, fextern);
	FILE* file = NULL;
    while (head != NULL) 
    {
        if (head)
        {
            if(!file)
                file = fopen(extern_name, "w");
            fprintf(file, "%s\t%d\n", head->name, head->address);
        }
        head = head->next;
    }
    if(file)
        fclose(file);
    free(extern_name);
}

/*----------------------------------------------------------------------------*/
/*function to write the code image and data image to the object file*/
void create_object_file(char* filename, codeimage* current, int DC, int IC, int data_image[])
{
    char* object_name = add_extenstion_to_file(filename, fobject);
    /* Open the object file for writing */
    FILE* object_file = fopen(object_name, "w"); 

    /* Display count of instructions and data in the object file */
    fprintf(object_file, "\t%d\t%d\n", IC - 100, DC);

    /* Write the code image to the object file */
    write_code_image_to_file_in_hexa(current, object_file);

    /* Write the data image to the object file */
    write_data_image_to_file_in_hexa(data_image, DC, IC, object_file);

    /* Close the object file */
    fclose(object_file);
    free(object_name);
}