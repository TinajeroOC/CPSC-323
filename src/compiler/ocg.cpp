#include "ocg.h"

ObjectCodeGenerator::ObjectCodeGenerator() { }

ObjectCodeGenerator::~ObjectCodeGenerator() { }

void ObjectCodeGenerator::generateInstruction(const std::string &operation, const unsigned int &operand) {
    instructionTable[memoryAddressCounter].address = memoryAddressCounter;
    instructionTable[memoryAddressCounter].operation = operation;
    instructionTable[memoryAddressCounter].operand = operand;
    memoryAddressCounter++;
}

bool ObjectCodeGenerator::existsSymbol(const std::string &identifier) {
    return symbolTable.find(identifier) != symbolTable.end();
}

void ObjectCodeGenerator::insertSymbol(const unsigned int &address, const std::string &identifier, const std::string &type) {
    symbolTable[identifier].address = address;
    symbolTable[identifier].identifier = identifier;
    symbolTable[identifier].type = type;
}

unsigned int ObjectCodeGenerator::getSymbolAddress(const std::string &identifier) {
    return symbolTable[identifier].address;
}

void ObjectCodeGenerator::backPatch(unsigned int &jumpAddress) {

}

unsigned int ObjectCodeGenerator::popJumpstack() {
    unsigned int top = jumpStack.top();
    jumpStack.pop();
    return top;
}