#include "pre_assembler.h"
/*----------------------------------------------------------------------------*/

/* This function calls the pre-assembler process. 
 * It takes the input file name and output file name as parameters.
 * It processes the output am file and expands macros.
 * It returns true if the pre-assembly was successful, false otherwise. */
bool call_pre_assembler(char *input_file, char *output_file) 
{
    int i, j;
    int cline = 0;
    FILE *src_file;
    FILE *dst_file;
    macro_table macros_list;
    char line[MAX_LENGTH_LINE];
    bool isMcr = false; /* is macro flag */
    int num_lines = 0;
    char **macro_lines = NULL;
    char *word;
    char line_copy[MAX_LENGTH_LINE]; /* line copy before strtok */
    macro *curr_macro;
    bool is_complete_successfully = true;

    src_file = fopen(input_file, "r");
    dst_file = fopen(output_file, "w");

    init_macro_table(&macros_list); /* init macro list */

    /* while loop to replace and get macros */
    while (fgets(line, sizeof(line), src_file))
    {
        cline++;
        strcpy(line_copy, line);
        word = strtok(line_copy, " \t\r\n"); /* get first word */
      
        if (!word) {
            fprintf(dst_file, "%s", line); /* Keep the line in the output file */
            continue;
        }

        word[strcspn(word, "\r\n")] = '\0';

        /*if is not macro read file, put lines and check for macros*/
        if (!isMcr) 
        {
            if (strcmp(word, START_DEFINE_MACRO_WORD) == 0) 
            {

                isMcr = true;
                word = strtok(NULL, " \t\n");


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
                    printf("ERROR: \"%s\" in %d line is reserved word, cannot be macro name.\n",word, cline);
                    is_complete_successfully = false;
                    macro_lines = (char **) malloc(sizeof(char *) * MAX_LENGTH_LINE);
                    macro_lines[num_lines] = (char *) malloc(strlen(word) + 1);
                    strcpy(macro_lines[num_lines++], word);
                }
            } 

            else 
            {
                curr_macro = get_macro_if_equals(&macros_list, word);
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
            if (strcmp(word, END_DEFINE_MACRO_WORD) == 0) 
            {
                add_macro(&macros_list, macro_lines[0], macro_lines + 1, num_lines - 1);
                for (j = 0; j < num_lines; j++)
                    free(macro_lines[j]);
                free(macro_lines);
                macro_lines = NULL;
                num_lines = 0;
                isMcr = false;
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
    return is_complete_successfully;
}
