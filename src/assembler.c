#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TOKENS 10
#define MAX_LABEL_LENGTH 20
#define MAX_OPCODE_LENGTH 10
#define MAX_OPERAND_LENGTH 20
#include "../include/assembler.h"

int locctr = 0; // Location counter

void pass1(char *filename, char *intermediate_file_name) {
    printf("*** Pass 1 *** \n");

    int err = -1; // Initialize an error flag

    FILE *file_ptr = fopen(filename, "r");

    if(file_ptr == NULL) {
        printf("Opening file failed\n");
        return;
    }

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

    FILE *intermediate_file = fopen(intermediate_file_name, "w");
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

void pass2(char *filename, char *object_file) {
    printf("*** Pass 2 *** \n");

    int err = -1; // Initialize an error flag

    FILE *file_ptr = fopen(filename, "r");
    FILE *object_fp = fopen(object_file, "w");
    FILE *listing_fp = fopen("listing.txt", "w"); 

    if(file_ptr == NULL) {
        printf("Opening intermediate file failed\n");
        return;
    }

    if (object_fp == NULL) {
        printf("Opening object file failed\n");
        return;
    }

    int locctr = 0, program_length; 
    char line[256];
    char label[MAX_LABEL_LENGTH];
    char opcode[MAX_OPCODE_LENGTH];
    char operand[MAX_OPERAND_LENGTH];
    char programName[MAX_LABEL_LENGTH];
    int starting_add = 0;

    load_opcode_table();

    // Read the first line and tokenize it
    fgets(line, sizeof(line), file_ptr);
    tokenize_line(line, label, opcode, operand);
    printf("Label: %s, Opcode: %s, Operand: %s\n", label, opcode, operand);

    if(strcmp(opcode, "START") == 0) {
        strcpy(programName, label);
        starting_add = hex_to_int(operand);

        program_length = locctr - starting_add + 1;

        fprintf(object_fp, "H^%6s^%06X^%06X\n", programName, starting_add, program_length);

    }

    char text_record[70] = ""; 
    int text_start = 0;         // To track the starting address of text records
    int text_length = 0;

    while (fgets(line, sizeof(line), file_ptr)) {

        tokenize_line(line, label, opcode, operand);

        if (strcmp(opcode, "END") == 0) {
            // Write the last text record
            if (text_length > 0) {
                fprintf(object_fp, "T^%06X^%02X%s\n", text_start, text_length / 2, text_record);
            }

            fprintf(object_fp, "E^%06X\n", starting_add);
            break;
        }

        

        char object_code[10] = "";
        // ***********************************
        if (is_opcode(opcode)) {  // If it's an instruction
            Opcode *op = get_opcode(opcode);
            int opcode_value = op->opcode;
            int address = get_symbol_address(operand);  


            if (address == -1) {
                printf("Error: Undefined symbol %s\n", operand);
                continue;  // Skip to the next line if symbol is not found
            }

            // Generate the object code (Opcode + Address)
            sprintf(object_code, "%02X%04X", opcode_value, address);
        } else if (strcmp(opcode, "WORD") == 0) {
            // WORD is a 3-byte constant
            sprintf(object_code, "%06X", atoi(operand));
        } else if (strcmp(opcode, "BYTE") == 0) {
            // BYTE can be a character constant or hex constant
            if (operand[0] == 'C') {
                // Character constant
                for (int i = 2; operand[i] != '\''; i++) {
                    sprintf(object_code + strlen(object_code), "%02X", operand[i]);
                }
            } else if (operand[0] == 'X') {
                // Hex constant
                strncpy(object_code, operand + 2, strlen(operand) - 3);
            }
        }
    }
}

int main() {
    printf("******************* Assembler Started *******************\n");
    char filename[] = "src/f1.txt";
    pass1(filename, "intermediate.txt");
    char intermediate_file[] = "intermediate.txt";
    pass2(intermediate_file, "objectFile.txt");
    return 0;
}