#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TOKENS 10
#define MAX_LABEL_LENGTH 20
#define MAX_OPCODE_LENGTH 10
#define MAX_OPERAND_LENGTH 20
#include "../include/assembler.h"

void pass1(char *filename) {
    printf("*** Pass1 *** \n");

    int err = -1; // Initialize an error flag

    FILE *file_ptr = fopen(filename, "r");

    if(file_ptr == NULL) {
        printf("Opening file failed\n");
        return;
    }

    int locctr = 0; // Location counter
    char line[256];
    char label[MAX_LABEL_LENGTH];
    char opcode[MAX_OPCODE_LENGTH];
    char operand[MAX_OPERAND_LENGTH];
    char *starting_add;

    load_opcode_table();

    // Read the first line and tokenize it
    fgets(line, sizeof(line), file_ptr);
    tokenize_line(line, label, opcode, operand);
    printf("Label: %s, Opcode: %s, Operand: %s\n", label, opcode, operand);

    FILE *intermediate_file = fopen("intermediate.txt", "w");
    if(intermediate_file == NULL) {
        fclose(file_ptr);
        printf("Error opening intermediate file\n");
        return;
    }

    if(strcmp(opcode, "START") == 0) {
        starting_add = operand;
        locctr = hex_to_int(starting_add);
        write_to_intermediate(intermediate_file, label, opcode, operand, locctr);

        printf("START found, Starting address: %s, Locctr: %04X\n", starting_add, locctr);

        fgets(line, sizeof(line), file_ptr);
        tokenize_line(line, label, opcode, operand);
    } else {
        locctr = 0; 
    }

    while(strcmp(opcode, "END") != 0) {

        if(label[0] != '\0') {
            int addr = get_symbol_address(label);

            if (addr != -1) { 
                err = 1;
                printf("Error: Label '%s' already present\n", label);
                fclose(file_ptr);
                fclose(intermediate_file);
                return;
            } else {
                insert_symbol(label, locctr);
            }
        }

        if(opcode[0] != '\0') {
            Opcode *op = get_opcode(opcode); // Search for opcode in optab

            if(op != NULL) {
                locctr += op->format; 
            } else if(strcmp(opcode, "WORD") == 0) {
                locctr += 3; 
            } else if(strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand); 
            } else if(strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand); 
            } else if(strcmp(opcode, "BYTE") == 0) {

                int length = calculate_byte_length(operand);
                locctr += length;

            } else {
                err = 1;
                printf("Error: Valid Opcode '%s' not found\n", opcode);
                fclose(file_ptr);
                fclose(intermediate_file);
                return;
            }
        }

        write_to_intermediate(intermediate_file, label, opcode, operand, locctr);

        fgets(line, sizeof(line), file_ptr);
        tokenize_line(line, label, opcode, operand);
    }

    // Write END line to intermediate file
    write_to_intermediate(intermediate_file, label, opcode, operand, locctr);

    fclose(file_ptr);
    fclose(intermediate_file);
    printf("\n*************************************************\n");
    printf("Pass 1 completed successfully");
    printf("\n*************************************************\n");
    printf("Sym Tab: \n");

    printSymTab();    
}


int main() {
    printf("******************* Assembler Started *******************\n");
    char filename[] = "src/f1.txt";
    pass1(filename);
    return 0;
}