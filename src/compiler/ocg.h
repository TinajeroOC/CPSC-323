#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <stack>

struct Instruction {
    unsigned int address;
    std::string operation;
    unsigned int operand;
};

struct Symbol {
    unsigned int address;
    std::string identifier;
    std::string type;
};

class ObjectCodeGenerator {
    public:
        ObjectCodeGenerator();
        ~ObjectCodeGenerator();
        void generateInstruction(const std::string &operation, const unsigned int &operand);
        void insertSymbol(const unsigned int &address, const std::string &identifier, const std::string &type);
        unsigned int getSymbolAddress(const std::string &identifier);
        bool existsSymbol(const std::string &identifier);
        void backPatch(unsigned int& jumpAddress);
        unsigned int popJumpstack();
        void writeInstructionTableToFile(std::ofstream &outputFile);
        void writeSymbolTableToFile(std::ofstream &outputFile);
    private:
        unsigned int instructionAddressCounter = 1;
        unsigned int symbolAddressCounter = 5000;
        std::map<unsigned int, Instruction> instructionTable;
        std::unordered_map<std::string, Symbol> symbolTable;
        std::stack<unsigned int> jumpStack;
};