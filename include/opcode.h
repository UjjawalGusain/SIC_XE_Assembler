#ifndef OPCODE_H
#define OPCODE_H
#define OPCODE_COUNT
#define MAX_OPCODES 59

typedef struct {
    char mnemonic[10];
    int opcode;
    int format; 
} Opcode;

// Load opcode table from file or hardcode it
void load_opcode_table();
Opcode *get_opcode(char *mnemonic);
int is_opcode(char *opcode);

#endif
