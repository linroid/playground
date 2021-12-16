cmake_minimum_required(VERSION 3.21)
project(assembler)

set(CMAKE_CXX_STANDARD 17)

add_executable(assembler main.cpp parser.cpp parser.h instruction.cpp instruction.h code.cpp code.h symbol_table.cpp symbol_table.h)
