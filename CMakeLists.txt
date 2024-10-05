# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SIC_XE_Assembler)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(include)

# Add all source files to the executable
file(GLOB SOURCES
    src/*.c  # This will include all .c files in the src directory
)

# Define the executable target
add_executable(sic_xe_assembler ${SOURCES})
