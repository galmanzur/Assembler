/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->
                                                ** Colors 🎨🎨 **
    The colors header file for terminal output.
    This file contains color codes for terminal output, including error, warning, success, and debug messages.
 ->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#ifndef COLORS_H
#define COLORS_H

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#include <stdio.h>

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#define COLOR_RED     "\x1b[31m" /* Error messages */

#define COLOR_RESET   "\x1b[0m" /* Reset to default color */

#define COLOR_YELLOW  "\x1b[33m" /* Warning messages */

#define COLOR_GREEN   "\x1b[92m" /* Success messages */

#define COLOR_PURPLE "\x1b[35m" /* Debug messages */

/*->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->*/

#endif /* COLORS_H */