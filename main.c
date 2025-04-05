/*
    
    _                           _     _           
   / \   ___ ___  ___ _ __ ___ | |__ | | ___ _ __ 
  / _ \ / __/ __|/ _ \ '_ ` _ \| '_ \| |/ _ \ '__|
 / ___ \\__ \__ \  __/ | | | | | |_) | |  __/ |   
/_/   \_\___/___/\___|_| |_| |_|_.__/|_|\___|_|     ©️Gal Manzur  
                                                       
*/
/*Purpose: This is the main file of the assembler program. It is responsible for handling the command line arguments.

 This is  assembler that takes an assembly language source file as input and generates an object file, entry file, and extern file.
    * The assembler consists of three main stages - calls each stage if the previous successfully completed:
            * 1. Pre-Assembler stage: handles macros and expands them in the source file
            * 2. First pass stage: handles the assembly language syntax and fills the symbol table
            * 3. Second pass stage: handles the assembly language syntax and fills the code image and data image:
                * 1. write entry file: writes the entry file if there are any entries in the symbol table 
                * 2. write extern file: writes the extern file with the external labels and their addresses
                * 3. write object file: writes the object file with the code image and data image 
            Then- free all memory used in the assembler
        
        checking if file is readable and if it is call pre-assembler function
        If the file is not readable, prints error message and exit*/

#include "main.h"


/*main function that use all other function of assembler to create our two pass
assembler*/
int main(int argc, char *argv[])
{
    int IC;
    int DC;
    int i;    
    int j;                        
    char *source_file, *file_after_preassembler; /*stores the file name, spreaded file name*/
    int data_image[2048] = {0}; /*data image buffer*/
    codeimage* code_table;  
    symbol* symbol_table;         
    externList* extern_list; 

    if (argc == 1)
    {
        /* if no file name is given as argument, print error message*/
        printf("ERROR: No file name as input.\n");
    }

    /*for loop to treat each file given as argument in the assembler manner*/
    for (i = 1; i < argc; i++)
    {    
        /*printing the file name given as argument*/
        printf("Processing file: %s\n", argv[i]);
        /*initializing the data image buffer to 0*/
        for(j = 0; j < 2048; j++)
            data_image[j] = 0;
        IC = 100; 
        DC = 0; 
        code_table = NULL;  
        symbol_table = NULL;         
        extern_list = NULL; 
    
        /* Preparing files to assembler - assumes the user provided file without extension */
        source_file = add_extenstion_to_file(argv[i], extension_file_source); /*changing name to name of file by adding file extension*/
        file_after_preassembler = add_extenstion_to_file(argv[i], extension_file_after_preassembler);/*changing name to name of file by adding file extension*/

        if(is_file_readable(source_file))
        {
            if(call_pre_assembler(source_file, file_after_preassembler))
            {
                printf("Pre-Assembler stage completed.\n");
                if(call_first_pass(&symbol_table, file_after_preassembler, &IC, &DC)) /*first pass stage*/
                {
                    printf("First pass completed.\n");
                    if(second_pass(argv[i], &code_table, &symbol_table, &DC, &IC, data_image, &extern_list)) /*second pass stage*/
                    {
                        printf("Second pass completed.\n");

                        printf("Assembler completed successfully.\n");
                    }
                    else
                    {
                        printf("ERROR: Second pass stage failed.\n");
                    }
                }
                else
                {
                    printf("ERROR: First pass stage failed.\n");
                }
            }
            else
            {
                printf("ERROR: Pre-Assembler stage failed.\n");
            }
        }
        else
        {
            printf("ERROR: File '%s' is not readable.\n", source_file);
        }
        
        /*desytoying and initializing all parameters used in this run*/

        /*freeing all memory used in the assembler*/
        free_symbol_table(symbol_table);
        /*destroy_codeimage(code_table);
        destroy_externlist(extern_list); */
        memset(data_image, 0, sizeof(data_image));
        free(source_file);
        free(file_after_preassembler);
    }
    return 0;
}