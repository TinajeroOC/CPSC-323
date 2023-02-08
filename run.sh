#!/bin/bash

# Compile CPP Files Using GCC Standard 2017
g++ -c -Wall -no-pie -m64 -std=c++17 -o compiler.o compiler.cpp 

# Link Object Files Using GCC Standard 2017
g++ -m64 -no-pie -o code.out compiler.o -std=c++17

# Run Executable (code.out)
./code.out

# Remove Unneeded Files
rm *.o
rm *.out