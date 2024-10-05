CC = gcc
CFLAGS = -Iinclude           # Include the header files from the 'include' directory

# Source files
SRC = src/assembler.c src/opcode.c src/symbol_table.c src/pass1.c src/pass2.c src/utils.c
OBJ = $(SRC:.c=.o)

# Target executable
TARGET = assembler

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $<

clean:
    rm -f $(OBJ) $(TARGET)
