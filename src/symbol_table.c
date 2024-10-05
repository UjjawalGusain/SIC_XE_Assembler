#include <stdio.h>
#include <string.h>
#include "../include/symbol_table.h"

int symCount = 0;

Symbol symTab[MAX_SYMBOLS];

void init_symbol_table() {
    symCount = 0;
}

void insert_symbol(const char *symbol, unsigned int address) {
    if(symCount > MAX_SYMBOLS) {
        printf("Maximum number of symbols exceeded\n");
        return;
    }

    strncpy(symTab[symCount].symbol, symbol, sizeof(symTab[symCount].symbol) - 1);
    symTab[symCount].symbol[ sizeof(symTab[symCount].symbol) - 1 ] = '\0';

    symTab[symCount].address = address;

    symCount++;
}

int get_symbol_address(const char *symbol) {

    for(int i = 0; i<symCount; i++) {

        if(strcmp(symTab[i].symbol, symbol) == 0) {
            return symTab[i].address;
        }

    }
    return -1;
}

void printSymTab() {
    int i = 0;
    for(i = 0; i<symCount; i++) {
        printf("Symbol: %s | Address: %d\n", symTab[i].symbol, symTab[i].address);
    }
}