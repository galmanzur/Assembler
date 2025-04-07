
#include "print_to_console_service.h"

/* Prints an error message in red using printf */
void print_error(int line, char *message)
{
    printf(COLOR_RED "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_RED "\n🚫 ERROR (line %d): %s\n" COLOR_RESET, line, message);
    printf(COLOR_RED "------------------------------------------------------- \n" COLOR_RESET);

}

/* Prints a global error message in red using printf */
void print_global_error(char *message)
{
    printf(COLOR_RED "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_RED "\n🚫 ERROR: %s\n" COLOR_RESET, message);
    printf(COLOR_RED "------------------------------------------------------- \n" COLOR_RESET);

}

/* Prints a warning message in yellow using printf */
void print_warning(int line, char *message)
{
    printf(COLOR_YELLOW "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_YELLOW "\n⚠️ WARNING (line %d): %s\n" COLOR_RESET, line, message);
    printf(COLOR_YELLOW "------------------------------------------------------- \n" COLOR_RESET);

}

void print_success(char *message)
{
    printf(COLOR_GREEN "\n------------------------------------------------------- " COLOR_RESET);
    printf(COLOR_GREEN "\n✅  SUCCESS: %s\n" COLOR_RESET, message);
    printf(COLOR_GREEN "------------------------------------------------------- \n" COLOR_RESET);
}

void print_process_file(char *filename)
{
    printf(COLOR_PURPLE "\n-------------------------------------------------------\n " COLOR_RESET);
    printf(COLOR_PURPLE "Processing file --->>> %s\n" COLOR_RESET, filename);
    printf(COLOR_PURPLE "------------------------------------------------------- \n" COLOR_RESET);
}