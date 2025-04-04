#include "pre_assembler.h"
/*----------------------------------------------------------------------------*/

void call_pre_assembler(char *input_file, char *output_file) 
{
    int i, j;
    int cline = 0;
    FILE *src_file;
    FILE *dst_file;
    macro_table macros_list;
    char line[MAX_LINE];
    bool isMcr = false; /* is macro flag */
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
        word = strtok(line_copy, " \t\r\n"); /* get first word */
      
        if (!word) {
            fprintf(dst_file, "%s", line); /* Keep the line in the output file */
            continue;
        }

        word[strcspn(word, "\r\n")] = '\0';

        /*if is not macro read file, put lines and check for macros*/
        if (!isMcr) 
        {
            if (strcmp(word, "mcr") == 0) 
            {

                isMcr = true;
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
            if (strcmp(word, "mcroend") == 0) 
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
        print_macro_table(&macros_list);
    }

    /*closing files*/
    fclose(src_file);
    fclose(dst_file);
    free_macro_table(&macros_list);
}

/*
void validate_macro_definition(FILE *src_file, macro_table *macros_list, char *word, int current_line) 
{
    if (!word || is_safe_word(word)) 
    {
        fprintf(stderr, "ERROR: \"%s\" in line %d is reserved word, cannot be macro name.\n", word, current_line);
        return;
    }
}

void spread_out_macro(FILE *dst_file, macro_table *macros_list, char *word, char *line) 
{
    macro *current_macro;
    int i;
    current_macro = get_macro(macros_list, word);
    if (current_macro != NULL) 
    {
        for (i = 0; i < current_macro->num_lines; i++) 
        {
            fprintf(dst_file, "%s", current_macro->lines[i]);
        }
    } 
    else 
    {
        fprintf(dst_file, "%s", line);
    }
}

void save_macro(macro_table *macros_list, char **macro_lines, int num_lines) 
{
    int j;
    if (!macro_lines || num_lines == 0) return;
    
    add_macro(macros_list, macro_lines[0], macro_lines + 1, num_lines - 1);
    
    for (j = 0; j < num_lines; j++)
        free(macro_lines[j]);
    
    free(macro_lines);
}*/
