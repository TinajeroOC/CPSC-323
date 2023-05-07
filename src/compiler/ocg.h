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
        void insertInstruction(const std::string &operation, const unsigned int &operand);
        unsigned int getInstructionAddressCounter();
        void insertSymbol(const std::string &identifier, const std::string &type);
        unsigned int getSymbolAddress(const std::string &identifier);
        bool existsSymbol(const std::string &identifier);
        void queueSymbol(const std::string &identifier);
        std::vector<std::string> getQueuedSymbols();
        void clearQueuedSymbols();
        void backPatch();
        void pushJumpstack();
        unsigned int popJumpstack();
        void writeInstructionTableToFile(std::ofstream &outputFile);
        void writeSymbolTableToFile(std::ofstream &outputFile);
    private:
        unsigned int instructionAddressCounter;
        unsigned int symbolAddressCounter;
        std::map<unsigned int, Instruction> instructionTable;
        std::unordered_map<std::string, Symbol> symbolTable;
        std::vector<std::string> queuedSymbols;
        std::stack<unsigned int> jumpStack;
};