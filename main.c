#include "main.h"

char *extension_file_source = ".as"; /*variable to store the extension of file as file*/
char *extension_file_after_preassembler = ".am";  /*varaiable to store the extension of spread file*/


/*main function that use all other function of assembler to create our two pass
assembler*/
int main(int argc, char *argv[])
{
    int i;                            
    char *source_file, *file_after_preassembler; /*stores the file name, spreaded file name*/
    /*printing no arguments were given*/
    if (argc == 1)
    {
        /*printing error to user of too few arguments*/
        printf("ERROR: No file name as input.\n");
    }

    /*for loop to treat each file given as argument in the assembler manner*/
    for (i = 1; i < argc; i++)
    {    
        int data_image[2048] = {0}; /*data image buffer of fixed size*/
        int IC = 100; /*initializing IC to 100*/
        int DC = 0; /*initializing DC to 0*/
        codeimage* code_table = NULL;  
        symbol* symbol_table = NULL;         
        externList* extern_list = NULL; 
        source_file = add_extension(argv[i], extension_file_source); /*changing name to name of file by adding file extension*/
        file_after_preassembler = add_extension(argv[i], extension_file_after_preassembler);/*changing name to name of file by adding file extension*/

        /*checking if file can be opened*/
        if(is_file_readable(source_file))
        {
            call_pre_assembler(source_file, file_after_preassembler); /*preassembler stage - warns only*/
            printf("Pre-Assembler stage completed.\n");
            call_first_pass(&symbol_table, file_after_preassembler, &IC, &DC); /*first pass stage*/
            printf("First pass completed.\n");
        }

        /*desytoying and initializing all parameters used in this run*/
        free_symbol_table(symbol_table);
        /*destroy_codeimage(code_table);
        destroy_externlist(extern_list); */
        memset(data_image, 0, sizeof(data_image));
        free(source_file);
        free(file_after_preassembler);
    }
    return 0;
}