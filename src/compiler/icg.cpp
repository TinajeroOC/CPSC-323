#include "icg.h"

SymbolTable::SymbolTable() { }

SymbolTable::~SymbolTable() { }

void SymbolTable::gen_instr(std::string op, int address, std::string oprnd) {
    instr_table[address, op];
}

void SymbolTable::insert_iden(int Memory_address, std::string lexeme, std::string type) {
    symbol_table[Memory_address, lexeme];
}

void SymbolTable::insert_op(int Memory_address, std::string lexeme, std::string type) {
    symbol_table[Memory_address, lexeme];
}