#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 100

typedef struct {
    char symbol[7]; // 6 chars + 1 for null
    unsigned int address : 24; // 24 bit address using bit field

} Symbol;

void init_symbol_table();
void insert_symbol(const char *symbol, unsigned int address);
int get_symbol_address(const char *symbol);
void printSymTab();

#endif