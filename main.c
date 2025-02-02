#include "main_assembler.h"
/* Main function */
int main(int argc, char *argv[]) 
{
    int i;
    /* Allocate memory for variables */
    char *line = NULL;
    char *token = NULL;
    char *am_file = NULL;
    char *ob_file;
    char *ext_file;
    char *ent_file;
    char *line_copy = NULL;
    char *as_file_original = NULL;
    char **registers = malloc(sizeof(char *) * NUM_OF_REGISTERS);
    char **directives = malloc(sizeof(char *) * NUM_OF_DIRECTIVES);
    symbol_table table;
    error_table errors_list;
    command_field command_table[NUM_COMMANDS];
    FILE *fp;

    /* Check for at least one .as code file */
    if (argc < 2) {
        printf("Usage: %s <filename1> <filename2> ... <filenameN>\n", argv[0]);
        return 1;
    }
    /* Run the assembler on each file */
    for (i = 1; i < argc; i++)
    {
        if(check_file(argv[i])) /* checks that the file is valid .as file (existing)*/
        {
            /* resetts allocations between files */
            if (line != NULL)
                line = NULL;
    		line = malloc(MAX_LINE_SIZE);
            if (am_file != NULL)
                am_file = NULL;
    		am_file = malloc(MAX_LINE_SIZE);
            if (as_file_original != NULL)
                as_file_original = NULL;
    		as_file_original = malloc(MAX_LINE_SIZE);
    		token = NULL;
    		line_copy = NULL;

            init_filenames(argv[i], &ob_file, &ext_file, &ent_file, NULL);
            /* calling assemble to start the assemble process */
            assemble(argv[i], &table, &errors_list, line, token, command_table, am_file, &as_file_original, registers, directives, line_copy, ob_file, ext_file, ent_file, &fp);
        }
    }
    /* Ended for all files, flush and kill */
    flush_main(registers, directives);
    return 0;
}
