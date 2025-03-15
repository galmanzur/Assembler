#include "pre_assembler.h"
/*----------------------------------------------------------------------------*/
/*function calling a macro from table and spreading it*/
void call_pre_assembler(char *input_file, char *output_file) 
{
    int i, j;
    int cline = 0;
    FILE *src_file;
    FILE *dst_file;
    macro_table macros_list;
    char line[MAX_LINE];
    bool is_macro_found = false; /* is macro flag */
    int num_lines = 0;
    char **macro_lines = NULL;
    char *word;
    char line_copy[MAX_LINE]; /* line copy before strtok */
    macro *curr_macro;

    src_file = fopen(input_file, "r");
    dst_file = fopen(output_file, "w");

    init_macro_table(&macros_list); /* init macro list */

    /* while loop to replace and get macros */
    while (fgets(line, sizeof(line), src_file))
    {
        cline++;
        strcpy(line_copy, line);
        word = strtok(line_copy, " \t\n");

        if (!word) {
            fprintf(dst_file, "%s", line); /* Keep the line in the output file */
            continue;
        }
        /*if is not macro read file, put lines and check for macros*/
        if (!is_macro_found) 
        {
            if (strcmp(word, "mcr") == 0) 
            {
                is_macro_found = true;
                word = strtok(NULL, " \t\n");

                /*checking if macro is safe*/
                if (!is_safe_word(word)) 
                {
                    macro_lines = (char **) malloc(sizeof(char *) * MAX_LINE);
                    macro_lines[num_lines] = (char *) malloc(strlen(word) + 1);
                    strcpy(macro_lines[num_lines++], word);

                } 
                else 
                {    
                    /*if macro is not safe print ERROR*/ 
                    printf("ERROR: \"%s\" in %d line is reserved word, cannot be macro name.\n",word, cline);
                    macro_lines = (char **) malloc(sizeof(char *) * MAX_LINE);
                    macro_lines[num_lines] = (char *) malloc(strlen(word) + 1);
                    strcpy(macro_lines[num_lines++], word);
                }
            } 

            else 
            {
                curr_macro = get_macro(&macros_list, word);
                if (curr_macro != NULL) 
                {
                    for (i = 0; i < curr_macro->num_lines; i++) 
                    {
                        fprintf(dst_file, "%s", curr_macro->lines[i]);
                    }
                } 
                else 
                {
                    fprintf(dst_file, "%s", line); /* Keep the line in the output file */
                }
            }
        } 
        else 
        {
            if (strcmp(word, "endmcr") == 0) 
            {
                add_macro(&macros_list, macro_lines[0], macro_lines + 1, num_lines - 1);
                for (j = 0; j < num_lines; j++)
                    free(macro_lines[j]);
                free(macro_lines);
                macro_lines = NULL;
                num_lines = 0;
                is_macro_found = false;
            } 

            else 
            {
                macro_lines[num_lines] = (char *) malloc(strlen(line) + 1);
                strcpy(macro_lines[num_lines++], line);
            }
        }
    }

    /*closing files*/
    fclose(src_file);
    fclose(dst_file);
    free_macro_table(&macros_list);
}