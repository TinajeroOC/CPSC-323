#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "parser.h"

const int instr_address = 5000;

class SymbolTable {
    public: 
        SymbolTable();
        ~SymbolTable();
        void gen_instr(std::string op, int address, std::string oprnd);
    private: 
        std::unordered_map<std::string, int> instr_table;
        std::unordered_map<std::string, int> symbol_table;
        bool check_iden(const std::string &symbol_check);
        void print_iden();
        void insert_iden(int Memory_address, std::string lexeme, std::string type);
        void insert_op(int Memory_address, std::string lexeme, std::string type);
};