#include "ocg.h"

ObjectCodeGenerator::ObjectCodeGenerator() { }

ObjectCodeGenerator::~ObjectCodeGenerator() { }

void ObjectCodeGenerator::queueSymbol(const std::string &identifier) {
    queuedSymbols.push_back(identifier);
}

std::vector<std::string> ObjectCodeGenerator::getQueuedSymbols() {
    return queuedSymbols;
}

void ObjectCodeGenerator::clearQueuedSymbols() {
    queuedSymbols.clear();
}

void ObjectCodeGenerator::generateInstruction(const std::string &operation, const unsigned int &operand) {
    Instruction instruction = {instructionAddressCounter, operation, operand};
    instructionTable[instructionAddressCounter] = instruction;
    instructionAddressCounter++;
}

void ObjectCodeGenerator::insertSymbol(const std::string &identifier, const std::string &type) {
    if (existsSymbol(identifier)) {
        throw std::runtime_error("Object Code Generation Error: Symbol '" + identifier + "' already exists.");
    }
    
    Symbol symbol = {symbolAddressCounter, identifier, type};
    symbolTable[identifier] = symbol;
    symbolAddressCounter++;
}

unsigned int ObjectCodeGenerator::getSymbolAddress(const std::string &identifier) {
    if (!existsSymbol(identifier)) {
        throw std::runtime_error("Object Code Generation Error: Symbol '" + identifier + "' does not exist.");
    }
    return symbolTable[identifier].address;
}

bool ObjectCodeGenerator::existsSymbol(const std::string &identifier) {
    return symbolTable.find(identifier) != symbolTable.end();
}

void ObjectCodeGenerator::backPatch(unsigned int &jumpAddress) {

}

unsigned int ObjectCodeGenerator::popJumpstack() {
    unsigned int top = jumpStack.top();
    jumpStack.pop();
    return top;
}

void ObjectCodeGenerator::writeInstructionTableToFile(std::ofstream &outputFile) {
    outputFile << std::left << std::setw(8) << "Address" << std::right << std::setw(16) << "Operation" << std::right << std::setw(16) << "Operand" << std::endl;
    outputFile << "----------------------------------------" << std::endl;

    for (auto itr = instructionTable.begin(); itr != instructionTable.end(); itr++) {
        std::string operand = std::to_string(itr->second.operand);
        if (itr->second.operand == 0) {
            operand = " ";
        }
        outputFile << std::left << std::setw(8) << itr->second.address << std::right << std::setw(16) << itr->second.operation << std::right << std::setw(16) << operand << std::endl;
    }

    outputFile << "----------------------------------------" << std::endl;
}

void ObjectCodeGenerator::writeSymbolTableToFile(std::ofstream &outputFile) {
    outputFile << std::left << std::setw(15) << "Identifier" << std::right << std::setw(15) << "MemoryLocation" << std::right << std::setw(15) << "Type" << std::endl;
    outputFile << "--------------------------------------------" << std::endl;

    for (auto itr = symbolTable.begin(); itr != symbolTable.end(); itr++) {
        outputFile << std::left << std::setw(15) << itr->second.identifier << std::right << std::setw(15) << itr->second.address << std::right << std::setw(15) << itr->second.type << std::endl;
    }

    outputFile << "--------------------------------------------" << std::endl;
}