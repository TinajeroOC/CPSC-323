#pragma once
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>

class SymbolTable {
    public: 
        SymbolTable();
        ~SymbolTable();
        void gen_instr();
    private: 
        void insert(const std::string &iden);
        bool check_iden(const std::string &symbol_check);
        void print_iden();
};