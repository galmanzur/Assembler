
#include "print_to_console_service.h"

/* This function prints an error message in red using printf.
 * It takes the line number and the error message as parameters. */
void print_error(int line_number, char *message)
{
    printf(COLOR_RED "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_RED "\n🚫 ERROR (line %d): %s\n" COLOR_RESET, line_number, message);
    printf(COLOR_RED "------------------------------------------------------- \n" COLOR_RESET);

}

/* This function prints an error message in red using printf and support adding arg between start str and end str. It takes also the line number
as parameter. */
void print_error_with_arg(int line_number, char *message_start, char *arg, char *message_end)
{
    printf(COLOR_RED "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_RED "\n🚫 ERROR (line %d): %s %s %s\n" COLOR_RESET, line_number, message_start, arg, message_end);
    printf(COLOR_RED "------------------------------------------------------- \n" COLOR_RESET);
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a global error message in red using printf.
 * It takes the error message as a parameter. */
void print_global_error(char *message)
{
    printf(COLOR_RED "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_RED "\n🚫 ERROR: %s\n" COLOR_RESET, message);
    printf(COLOR_RED "------------------------------------------------------- \n" COLOR_RESET);

}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a warning message in yellow using printf.
 * It takes the line number and the warning message as parameters. */
void print_warning(int line_number, char *message)
{
    printf(COLOR_YELLOW "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_YELLOW "\n⚠️ WARNING (line %d): %s\n" COLOR_RESET, line_number, message);
    printf(COLOR_YELLOW "------------------------------------------------------- \n" COLOR_RESET);

}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a success message in green using printf.
 * It takes the success message as a parameter. */
void print_success(char *message)
{
    printf(COLOR_GREEN "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_GREEN "\n✅ %s\n" COLOR_RESET, message);
    printf(COLOR_GREEN "------------------------------------------------------- \n" COLOR_RESET);
}

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

/* This function prints a process file message in purple using printf.
 * It takes the file name as a parameter. */
void print_process_file(char *filename)
{
    printf(COLOR_PURPLE "\n-------------------------------------------------------\n " COLOR_RESET);
    printf(COLOR_PURPLE "Processing file --->>> %s\n" COLOR_RESET, filename);
    printf(COLOR_PURPLE "------------------------------------------------------- \n" COLOR_RESET);
}