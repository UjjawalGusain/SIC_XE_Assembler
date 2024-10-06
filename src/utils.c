#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <ctype.h>
#define MAX_TOKENS 10
#include "../include/utils.h"

void write_to_intermediate(FILE *file, char *label, char *opcode, char *operand, int locctr) {
    fprintf(file, "%-10s %-10s %-10s %04X\n", label, opcode, operand, locctr);  // Example format
}

void trim_whitespace(char *str) {

    while(str && isspace((unsigned char) *str)) 
        str++;

    if(*str == '\0')
        return;
    
    char *end = str + strlen(str) - 1;

    while(end > str && isspace((unsigned char) *end)) 
        end--;

    *(end + 1) = '\0';
}

void trim_comments(char *str) {
    char *end = str + strlen(str) - 1;

    while(end > str && ((unsigned char) *end) != ';') 
        end--;
    
    if(end == str) 
        return;

    *(end) = '\0';
}

void tokenize_line(char *line, char *label, char *opcode, char *operand) {

    trim_whitespace(line);
    trim_comments(line);
    char delim[] = " \t";

    char *token = strtok(line, delim);
    int token_count = 0;
    char *tokens[MAX_TOKENS];
    while (token) {
        tokens[token_count++] = token;
        token = strtok(NULL, delim);
    }

    label[0] = '\0';
    opcode[0] = '\0';
    operand[0] = '\0';
    if(token_count == 1) {
        strcpy(opcode, tokens[0]);
    } else if(token_count == 2) {
        strcpy(opcode, tokens[0]);
        strcpy(operand, tokens[1]);
    } else {
        strcpy(label, tokens[0]);
        strcpy(opcode, tokens[1]);
        strcpy(operand, tokens[2]);
    }

    printf("Label: %s, Opcode: %s, Operand: %s\n", label, opcode, operand);

}

int hex_to_int(const char *hex_str) {
    return (int)strtol(hex_str, NULL, 16); 
}

int calculate_byte_length(const char *operand) {
    if (operand[0] == 'C') { 
        // The format is C'string' (e.g., C'EOF' or C'AB')
        int length = strlen(operand) - 3; // Exclude the leading 'C' and the quotes
        return length; 
    } 
    else if (operand[0] == 'X') { 
        // The format is X'hexstring' (e.g., X'1A3F')
        int length = strlen(operand) - 3; // Exclude the leading 'X' and the quotes
        return length / 2; // Each byte is represented by 2 hex digits
    } 
    else {
        // If it’s a single decimal byte, it's valid
        return 1; // Treat decimal values as 1 byte for simplicity
    }
    return 0; // Default case (should not reach here if input is valid)
}