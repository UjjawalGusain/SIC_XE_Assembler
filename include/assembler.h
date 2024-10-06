#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "opcode.h"
#include "symbol_table.h"
#include "utils.h"

void pass1(char *filename, char *intermediate_file_name); // Pass 1: Generate symbol table
void pass2(char *filename, char *object_file_name); // Pass 2: Generate object code

#endif