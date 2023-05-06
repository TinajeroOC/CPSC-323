#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "token.h"
#include "ocg.h"

class Parser {
    public:
        Parser(std::ofstream &outputFile, std::vector<Token> &tokens);
        ~Parser();
        void parse();
    private:
        std::ofstream &outputFile;
        std::vector<Token> &tokens;
        std::vector<Token>::iterator itr;
        Token token, save;
        ObjectCodeGenerator generator;
        void logError(const std::vector<std::string> &expected, const std::string &lexeme, const int &line);
        bool nextToken();
        void procedureR1();
        void procedureR2();
        void procedureR3();
        void procedureR4();
        void procedureR5();
        void procedureR6();
        void procedureR7();
        void procedureR8();
        void procedureR9();
        void procedureR10();
        void procedureR11();
        void procedureR12();
        void procedureR13();
        void procedureR14();
        void procedureR15();
        void procedureR16();
        void procedureR17();
        void procedureR18();
        void procedureR19();
        void procedureR20();
        void procedureR21();
        void procedureR22();
        void procedureR23();
        void procedureR24();
        void procedureR25();
        void procedureR26();
        void procedureR27();
        void procedureR28();
        void procedureR29();
        void procedureR30();
        void procedureR31();
        void procedureR32();
        void procedureR33();
        void procedureR34();
        void procedureR35();
        void procedureR36();
        void procedureR37();
        void procedureR38();
};