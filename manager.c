#include "manager.h"

/*the assembly language opcodes array, the index of each opcode in the array 
is given by the value it gets in machine language*/
const char *opcodes[NUM_OPCODES] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};

/*the 8 registers r0-r7 of the CPU placed in the imaginery computer for this 
task*/
const char *registers[NUM_REGISTERS] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

/*array of valid instructions for data types of the assembler*/
const char *instructions[NUM_INSTRUCTIONS] = {".data", ".string", ".entry", ".extern"};

const opcode_param_and_addressing_table opcodes_table[] ={
{ALLBUT2, ALLBUT02}, /*mov*/
{ALLBUT2,ALLBUT2}, /*cmp*/
{ALLBUT2, ALLBUT2}, /*add*/
{ALLBUT2, ALLBUT02}, /*sub*/
{NONE, ALLBUT02}, /*not*/
{NONE, ALLBUT02}, /*clr*/
{NOTHINGBUT1, ALLBUT02}, /*lea*/
{NONE, ALLBUT02}, /*inc*/
{NONE, ALLBUT02}, /*dec*/
{NONE, ALLBUT0}, /*jmp*/
{NONE, ALLBUT0}, /*bne*/
{NONE, ALLBUT02}, /*red*/
{NONE, ALLBUT2}, /*prn*/
{NONE, ALLBUT0}, /*jsr*/
{NONE, NONE}, /*rts*/
{NONE, NONE}};  /*stop*/

