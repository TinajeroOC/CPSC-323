#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "parser.h"
#include <stack>

struct instr {
    std::string id;
    int address;
    std::string type;
} symbolTable;

class SymbolTable {
    public: 
        SymbolTable();
        ~SymbolTable();
        void gen_instr(std::string op, int address);
        void back_patch(int& jump_address);
    private: 
        std::unordered_map<std::string, int> instr_table;
        bool check_iden(const std::string &symbol_check);
        void print_iden();
        void insert_iden(int Memory_address, std::string lexeme, std::string type);
        void insert_op(int Memory_address, std::string lexeme, std::string type);
        int pop_jumpstack();
        std::stack<int> jump_stack;
};