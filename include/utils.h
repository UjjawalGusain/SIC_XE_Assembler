#ifndef UTILS_H
#define UTILS_H

void tokenize_line(char *line, char *label, char *opcode, char *operand);
int hex_to_int(const char *hex);        // Convert hex string to integer
void print_error(char *message);  // Print error message
void write_to_intermediate(FILE *file, char *label, char *opcode, char *operand, int locctr);
int calculate_byte_length(const char *operand);

#endif
