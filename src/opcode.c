#include <stdio.h>
#include <string.h>
#include "../include/opcode.h"

Opcode opTab[MAX_OPCODES];

void load_opcode_table() {
    // Initialize the opTab array with mnemonic, opcode, and format
    strcpy(opTab[0].mnemonic, "ADD");
    opTab[0].opcode = 0x18;
    opTab[0].format = 3;

    strcpy(opTab[1].mnemonic, "ADDF");
    opTab[1].opcode = 0x58;
    opTab[1].format = 3;

    strcpy(opTab[2].mnemonic, "ADDR");
    opTab[2].opcode = 0x90;
    opTab[2].format = 2;

    strcpy(opTab[3].mnemonic, "AND");
    opTab[3].opcode = 0x40;
    opTab[3].format = 3;

    strcpy(opTab[4].mnemonic, "CLEAR");
    opTab[4].opcode = 0xB4;
    opTab[4].format = 2;

    strcpy(opTab[5].mnemonic, "COMP");
    opTab[5].opcode = 0x28;
    opTab[5].format = 3;

    strcpy(opTab[6].mnemonic, "COMPF");
    opTab[6].opcode = 0x88;
    opTab[6].format = 3;

    strcpy(opTab[7].mnemonic, "COMPR");
    opTab[7].opcode = 0xA0;
    opTab[7].format = 2;

    strcpy(opTab[8].mnemonic, "DIV");
    opTab[8].opcode = 0x24;
    opTab[8].format = 3;

    strcpy(opTab[9].mnemonic, "DIVF");
    opTab[9].opcode = 0x64;
    opTab[9].format = 3;

    strcpy(opTab[10].mnemonic, "DIVR");
    opTab[10].opcode = 0x9C;
    opTab[10].format = 2;

    strcpy(opTab[11].mnemonic, "FIX");
    opTab[11].opcode = 0xC4;
    opTab[11].format = 1;

    strcpy(opTab[12].mnemonic, "FLOAT");
    opTab[12].opcode = 0xC0;
    opTab[12].format = 1;

    strcpy(opTab[13].mnemonic, "HIO");
    opTab[13].opcode = 0xF4;
    opTab[13].format = 1;

    strcpy(opTab[14].mnemonic, "J");
    opTab[14].opcode = 0x3C;
    opTab[14].format = 3;

    strcpy(opTab[15].mnemonic, "JEQ");
    opTab[15].opcode = 0x30;
    opTab[15].format = 3;

    strcpy(opTab[16].mnemonic, "JGT");
    opTab[16].opcode = 0x34;
    opTab[16].format = 3;

    strcpy(opTab[17].mnemonic, "JLT");
    opTab[17].opcode = 0x38;
    opTab[17].format = 3;

    strcpy(opTab[18].mnemonic, "JSUB");
    opTab[18].opcode = 0x48;
    opTab[18].format = 3;

    strcpy(opTab[19].mnemonic, "LDA");
    opTab[19].opcode = 0x00;
    opTab[19].format = 3;

    strcpy(opTab[20].mnemonic, "LDB");
    opTab[20].opcode = 0x68;
    opTab[20].format = 3;

    strcpy(opTab[21].mnemonic, "LDCH");
    opTab[21].opcode = 0x50;
    opTab[21].format = 3;

    strcpy(opTab[22].mnemonic, "LDF");
    opTab[22].opcode = 0x70;
    opTab[22].format = 3;

    strcpy(opTab[23].mnemonic, "LDL");
    opTab[23].opcode = 0x08;
    opTab[23].format = 3;

    strcpy(opTab[24].mnemonic, "LDS");
    opTab[24].opcode = 0x6C;
    opTab[24].format = 3;

    strcpy(opTab[25].mnemonic, "LDT");
    opTab[25].opcode = 0x74;
    opTab[25].format = 3;

    strcpy(opTab[26].mnemonic, "LDX");
    opTab[26].opcode = 0x04;
    opTab[26].format = 3;

    strcpy(opTab[27].mnemonic, "LPS");
    opTab[27].opcode = 0xD0;
    opTab[27].format = 3;

    strcpy(opTab[28].mnemonic, "MUL");
    opTab[28].opcode = 0x20;
    opTab[28].format = 3;

    strcpy(opTab[29].mnemonic, "MULF");
    opTab[29].opcode = 0x60;
    opTab[29].format = 3;

    strcpy(opTab[30].mnemonic, "MULR");
    opTab[30].opcode = 0x98;
    opTab[30].format = 2;

    strcpy(opTab[31].mnemonic, "NORM");
    opTab[31].opcode = 0xC8;
    opTab[31].format = 1;

    strcpy(opTab[32].mnemonic, "OR");
    opTab[32].opcode = 0x44;
    opTab[32].format = 3;

    strcpy(opTab[33].mnemonic, "RD");
    opTab[33].opcode = 0xD8;
    opTab[33].format = 3;

    strcpy(opTab[34].mnemonic, "RMO");
    opTab[34].opcode = 0xAC;
    opTab[34].format = 2;

    strcpy(opTab[35].mnemonic, "RSUB");
    opTab[35].opcode = 0x4C;
    opTab[35].format = 3;

    strcpy(opTab[36].mnemonic, "SHIFT");
    opTab[36].opcode = 0xA4;
    opTab[36].format = 2;

    strcpy(opTab[37].mnemonic, "SHIFTR");
    opTab[37].opcode = 0xA8;
    opTab[37].format = 2;

    strcpy(opTab[38].mnemonic, "SIO");
    opTab[38].opcode = 0xF0;
    opTab[38].format = 1;

    strcpy(opTab[39].mnemonic, "SSK");
    opTab[39].opcode = 0xEC;
    opTab[39].format = 3;

    strcpy(opTab[40].mnemonic, "STA");
    opTab[40].opcode = 0x0C;
    opTab[40].format = 3;

    strcpy(opTab[41].mnemonic, "STB");
    opTab[41].opcode = 0x78;
    opTab[41].format = 3;

    strcpy(opTab[42].mnemonic, "STCH");
    opTab[42].opcode = 0x54;
    opTab[42].format = 3;

    strcpy(opTab[43].mnemonic, "STF");
    opTab[43].opcode = 0x80;
    opTab[43].format = 3;

    strcpy(opTab[44].mnemonic, "STI");
    opTab[44].opcode = 0xD4;
    opTab[44].format = 3;

    strcpy(opTab[45].mnemonic, "STL");
    opTab[45].opcode = 0x14;
    opTab[45].format = 3;

    strcpy(opTab[46].mnemonic, "STS");
    opTab[46].opcode = 0x7C;
    opTab[46].format = 3;

    strcpy(opTab[47].mnemonic, "STSW");
    opTab[47].opcode = 0xE8;
    opTab[47].format = 3;

    strcpy(opTab[48].mnemonic, "STT");
    opTab[48].opcode = 0x84;
    opTab[48].format = 3;

    strcpy(opTab[49].mnemonic, "STX");
    opTab[49].opcode = 0x10;
    opTab[49].format = 3;

    strcpy(opTab[50].mnemonic, "SUB");
    opTab[50].opcode = 0x1C;
    opTab[50].format = 3;

    strcpy(opTab[51].mnemonic, "SUBF");
    opTab[51].opcode = 0x5C;
    opTab[51].format = 3;

    strcpy(opTab[52].mnemonic, "SUBR");
    opTab[52].opcode = 0x94;
    opTab[52].format = 2;

    strcpy(opTab[53].mnemonic, "SVC");
    opTab[53].opcode = 0xB0;
    opTab[53].format = 2;

    strcpy(opTab[54].mnemonic, "TD");
    opTab[54].opcode = 0xE0;
    opTab[54].format = 3;

    strcpy(opTab[55].mnemonic, "TIO");
    opTab[55].opcode = 0xF8;
    opTab[55].format = 1;

    strcpy(opTab[56].mnemonic, "TIX");
    opTab[56].opcode = 0x2C;
    opTab[56].format = 3;

    strcpy(opTab[57].mnemonic, "TIXR");
    opTab[57].opcode = 0xB8;
    opTab[57].format = 2;

    strcpy(opTab[58].mnemonic, "WD");
    opTab[58].opcode = 0xDC;
    opTab[58].format = 3;
}

Opcode *get_opcode(char *mnemonic) {

    int i;
    for(i = 0; i<MAX_OPCODES; i++) {
        if(strcmp(opTab[i].mnemonic, mnemonic) == 0) {
            return &opTab[i];
        }
    }
    return NULL;
}

int is_opcode(char *opcode) {
    int i;
    for(i = 0; i<MAX_OPCODES; i++) {
        if(strcmp(opTab[i].mnemonic, opcode) == 0) {
            return 1;
        }
    }
    return 0;
}