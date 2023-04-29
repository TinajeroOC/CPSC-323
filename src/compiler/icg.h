#pragma once
#include <map>
#include <string>
#include <iostream>
#include <iomanip>

class SymbolTable {
    public: 
        SymbolTable();
    private: 
        void insert(const std::string &lexeme, const int &line, int Memory_address);
};