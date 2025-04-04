#include "assembler_config_data.h"

/*const char *opcodes[NUM_OPCODES] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};*/

const char *registers[NUM_REGISTERS] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

/*array of valid instructions for data types of the assembler*/
const char *instructions[NUM_INSTRUCTIONS] = {".data", ".string", ".entry", ".extern"};

const opcode opcodes[NUM_OPCODES] = {
    {"mov", 0, 0, 2},
    {"cmp", 1, -1, 2},
    {"add", 2, 1, 2},
    {"sub", 2, 2, 2},
    {"lea", 4, -1, 2},
    {"clr", 5, 1, 1},
    {"not", 5, 2, 1},
    {"inc", 5, 3, 1},
    {"dec", 5, 4, 1},
    {"jmp", 9, 1, 1},
    {"bne", 9, 2, 1},
    {"jsr", 9, 3, 1},
    {"red", 12, -1, 1},
    {"prn", 13, -1, 1},
    {"rts", 14, -1, 0},
    {"stop", 15, -1 , 0}
};
