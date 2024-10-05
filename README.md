sicxe-assembler/
│
├── include/                     # Header files
│   ├── assembler.h              # Main assembler functions and definitions
│   ├── opcode.h                 # Opcode table functions and definitions
│   ├── symbol_table.h           # Symbol table functions and definitions
│   └── utils.h                  # Utility functions and common definitions
│
├── src/                         # Source code files
│   ├── assembler.c              # Main assembler logic
│   ├── opcode.c                 # Opcode table management
│   ├── symbol_table.c           # Symbol table management
│   ├── pass1.c                  # Pass 1 logic
│   ├── pass2.c                  # Pass 2 logic
│   ├── utils.c                  # Helper functions
│
├── tests/                       # Test cases for each module
│   ├── test_program.asm         # Sample SIC/XE assembly program
│   ├── test_opcode.c            # Unit tests for opcode handling
│   ├── test_symbol_table.c      # Unit tests for symbol table handling
│   └── test_assembler.c         # Integration tests for the assembler
│
├── Makefile                     # Build instructions for the project
└── README.md                    # Documentation and instructions


Example file to read:

File name: PROG
*******************************************************************
PROG    START   1000      ; Starting address                      *
FIRST   LDA     NUM       ; Load value from NUM into accumulator  *
        ADD     COUNT     ; Add COUNT to accumulator              *
        STA     TOTAL     ; Store result in TOTAL                 *
        JLT     FIRST     ; Jump to FIRST if less than zero       *
        END                                                       *
                                                                  *
NUM     WORD    5         ; Define NUM as 5                       *
COUNT   WORD    10        ; Define COUNT as 10                    *
TOTAL   RESW    1         ; Reserve 1 word for TOTAL              *
*******************************************************************


run command:
gcc src/assembler.c src/utils.c src/opcode.c src/symbol_table.c src/pass1.c src/pass2.c -o assembler -Iinclude

assembler.exe

