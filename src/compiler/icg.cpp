#include "icg.h"

SymbolTable::SymbolTable() { }

SymbolTable::~SymbolTable() { }

void SymbolTable::gen_instr(std::string op, int address) {
    instr_table.insert({op, address});
    Memory_address++;
}

void SymbolTable::insert_iden(int Memory_address, std::string lexeme, std::string type) {
    symbolTable.address = Memory_address;
    symbolTable.id = lexeme;
    symbolTable.type = type;
}

void SymbolTable::insert_op(int Memory_address, std::string lexeme, std::string type) {
    symbolTable.address = Memory_address;
    symbolTable.id = lexeme;
    symbolTable.type = type;
}

void SymbolTable::back_patch(int& jump_address) {

}

int SymbolTable::pop_jumpstack() {
    int hold = jump_stack.top();
    jump_stack.pop();
    return hold;
}