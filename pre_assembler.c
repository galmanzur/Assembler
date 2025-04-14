#include "pre_assembler.h"

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function calls the pre-assembler process. 
 * It takes the input file name and output file name as parameters.
 * It processes the output am file and expands macros.
 * It returns true if the pre-assembly was successful, false otherwise. */
bool call_pre_assembler(char *input_file, char *output_file) 
{
    int i, j;
    int current_line = 0;
    FILE *source_file;
    FILE *destination_file;
    macro_table macro_table;
    char line[MAX_LENGTH_LINE];
    
    /* Kind of flag */
    bool is_process_macro = false; 

    int num_lines = 0;
    char **macro_lines = NULL;
    char *word;
    char line_copy[MAX_LENGTH_LINE]; 
    macro *current_macro_to_process;
    bool is_complete_successfully = true;

    /* Open the files */
    source_file = fopen(input_file, "r");
    destination_file = fopen(output_file, "w");

    /* Creates a new macro table */
    init_macro_table(&macro_table); /* init macro_table */

    /* Replace and get macros */
    while (fgets(line, sizeof(line), source_file))
    {
        current_line++;
        strcpy(line_copy, line);
        word = strtok(line_copy, " \t\r\n"); /* get first word */
      
        if (!word) {
            fprintf(destination_file, "%s", line); /* keep the line in the output file, there no need to do anything */
            continue;
        }

        word[strcspn(word, "\r\t\n")] = '\0';

        /*if is not macro read file, put lines and check for macros*/
        if (!is_process_macro) 
        {
            if (strcmp(word, START_DEFINE_MACRO_WORD) == 0) 
            {

                is_process_macro = true;
                word = strtok(NULL, " \r\t\n");


                /*checking if macro is safe*/
                if (!is_safe_word(word)) 
                {
                    macro_lines = (char **) malloc(sizeof(char *) * MAX_LENGTH_LINE);
                    macro_lines[num_lines] = (char *) malloc(strlen(word) + 1);
                    strcpy(macro_lines[num_lines++], word);

                } 
                else 
                {    
                    /*if macro is not safe print ERROR*/ 
                    print_error_with_arg(current_line, "Reserved word", word, "and can not be a macro name.");
                    is_complete_successfully = false;
                    macro_lines = (char **) malloc(sizeof(char *) * MAX_LENGTH_LINE);
                    macro_lines[num_lines] = (char *) malloc(strlen(word) + 1);
                    strcpy(macro_lines[num_lines++], word);
                }
            } 

            else 
            {
                current_macro_to_process = get_macro_if_equals(&macro_table, word);
                if (current_macro_to_process != NULL) 
                {
                    for (i = 0; i < current_macro_to_process->num_lines; i++) 
                    {
                        fprintf(destination_file, "%s", current_macro_to_process->lines[i]);
                    }
                } 
                else 
                {
                    fprintf(destination_file, "%s", line); /* Keep the line in the output file */
                }
            }
        } 
        else 
        {
            if (strcmp(word, END_DEFINE_MACRO_WORD) == 0) 
            {
                add_macro(&macro_table, macro_lines[0], macro_lines + 1, num_lines - 1);
                for (j = 0; j < num_lines; j++)
                    free(macro_lines[j]);
                free(macro_lines);
                macro_lines = NULL;
                num_lines = 0;
                is_process_macro = false;
            } 

            else 
            {
                macro_lines[num_lines] = (char *) malloc(strlen(line) + 1);
                strcpy(macro_lines[num_lines++], line);
            }
        }
    }

    /*closing files*/
    fclose(source_file);
    fclose(destination_file);
    free_macro_table(&macro_table);
    return is_complete_successfully;
}
