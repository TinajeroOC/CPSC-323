#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "token.h"
#include "lexer.h"
#include "parser.h"

class Compiler {
    public:
        Compiler();
        ~Compiler();
        void run(const std::string &sourceFileName);
    private:
        std::ifstream inputFile;
        std::ofstream outputFile;
        std::vector<Token> tokens;
        std::string getFormattedDate(const std::string &format);
        bool hasFileExtension(const std::string &fileName, const std::string &fileExtension);
};