#include "manager.h"

const char *registers[NUMBER_OF_REGISTERS] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

const char *directives_str[NUMBER_OF_DIRECTIVES] = {".data", ".string", ".entry", ".extern"};

/* The opcodes of the assembler. Each opcode has a name, an opcode number, a function code, and the number of parameters it takes. */
const opcode opcodes[NUMBER_OF_OPCODES] = {{"mov", 0, 0, 2}, {"cmp", 1, 0, 2}, {"add", 2, 1, 2}, 
                                          {"sub", 2, 2, 2}, {"lea", 4, 0, 2}, {"clr", 5, 1, 1},
                                          {"not", 5, 2, 1}, {"inc", 5, 3, 1}, {"dec", 5, 4, 1},
                                          {"jmp", 9, 1, 1}, {"bne", 9, 2, 1}, {"jsr", 9, 3, 1}, 
                                          {"red", 12, 0, 1}, {"prn", 13, 0, 1}, {"rts", 14, 0, 0}, 
                                          {"stop", 15, 0 , 0}};
                                          /* (name,  opcode number, funct, number of params) */
