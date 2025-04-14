/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->    
    _                           _     _           
   / \   ___ ___  ___ _ __ ___ | |__ | | ___ _ __ 
  / _ \ / __/ __|/ _ \ '_ ` _ \| '_ \| |/ _ \ '__|
 / ___ \\__ \__ \  __/ | | | | | |_) | |  __/ |   
/_/   \_\___/___/\___|_| |_| |_|_.__/|_|\___|_|     ©️ By Gal Manzur  
                                                       
*/
/*This is the main file of the assembler program. 
    * This assembler takes an assembly language source file as input and generates an object file, entry file, and extern file.
    * The assembler contains of three main stages - calls each stage if the previous successfully completed:
        1. Pre-Assembler stage: handles macros and expands them in the source file
        2. First pass stage: handles the assembly language syntax and fills the symbol table
        3. Second pass stage: handles the assembly language syntax and fills the code image and data image:
                * write entry file: writes the entry file if there are any entries in the symbol table 
                * write extern file: writes the extern file with the external labels and their addresses
                * write object file: writes the object file with the code image and data image 
        ** And obviously frees all memory used in the assembler */

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include "main.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This is the main function of the assembler program.
 It takes command line arguments for input file names, processes each file, and generates the output files.
 Calls the pre-assembler, first pass, and second pass functions. */
int main(int argc, char *argv[])
{
    int IC;
    int DC;
    int i;                         
    char *source_file, *file_after_preassembler; /* stores the file name, spreaded file name*/
    int data_image[DATA_IMAGE_SIZE] = {0}; /* data image buffer */
    bool is_first_pass_success = false;
    codeimage* code_table = NULL; 
    symbol* symbol_table = NULL; 
    externList* extern_list = NULL; 

    if (argc == 1)
    {
        /* If no file name is given as argument, print error message */
        print_global_error("No file name as an input.");
    }

    /* For each file name given as argument */
    for (i = 1; i < argc; i++)
    {    
        /* Print the name of the file being processed */
        print_process_file(argv[i]);

        /* Initialize the instruction counter (IC) and data counter (DC) */
        IC = START_VALUE_OF_IC; 
        DC = START_VALUE_OF_DC; 
    
        /* Preparing files to assembler - assumes the user provided file without extension */
        source_file = add_extension_to_file(argv[i], extension_file_source); /*changing name to name of file by adding file extension*/
        file_after_preassembler = add_extension_to_file(argv[i], extension_file_after_preassembler);/*changing name to name of file by adding file extension*/

        if(is_file_readable(source_file))
        {
            if(call_pre_assembler(source_file, file_after_preassembler))
            {
                print_success("Pre-Assembler stage completed.");
                if(call_first_pass(&symbol_table, file_after_preassembler, &IC, &DC)) /*first pass stage*/
                {
                    print_success("First pass completed.");
                    is_first_pass_success = true;
                    if(call_second_pass(argv[i], &code_table, &symbol_table, &DC, &IC, data_image, &extern_list, is_first_pass_success)) /*second pass stage*/
                    {
                        print_success("Second pass completed.");

                        print_success("Assembler completed successfully. 💯");
                    }
                    else
                        print_global_error("Second pass stage failed.");
                }
                else
                {
                    /* Display errors if there are more */
                    call_second_pass(argv[i], &code_table, &symbol_table, &DC, &IC, data_image, &extern_list, is_first_pass_success);
                }              
            }
            else
            {
                /* Display errors if there are more */
                call_first_pass(&symbol_table, file_after_preassembler, &IC, &DC);
                call_second_pass(argv[i], &code_table, &symbol_table, &DC, &IC, data_image, &extern_list, is_first_pass_success);
            }
                
        }
        
        /* Freeing all memory used in the assembler */
        free_symbol_table(symbol_table);
        free_code_image(code_table);
        free_extern_list(extern_list); 
        memset(data_image, 0, DATA_IMAGE_SIZE);
        free(source_file);
        free(file_after_preassembler);
    }
    return 0;
}