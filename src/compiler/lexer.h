#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include "token.h"

const std::unordered_set<std::string> keywords = {"int", "if", "else", "fi", "while", "endwhile", "return", "get", "put", "bool", "real", "function", "true", "false"};
const std::unordered_set<std::string> operators = {"==", "!=", ">", "<", "<=", "=>", "*", "/", "+", "-", "="};
const std::unordered_set<std::string> separators = {"#", "{", "}", "(", ")", ",", ";"};

class Lexer {
    public:
        Lexer(std::ifstream &inputFile, std::ofstream &outputFile, std::vector<Token> &tokens);
        ~Lexer();
        void tokenize();
        void writeTokensToFile();
    private:
        std::ifstream &inputFile;
        std::ofstream &outputFile;
        std::vector<Token> &tokens;
        bool isIdentifier(const std::string &lexeme);
        bool isInteger(const std::string &lexeme);
        bool isReal(const std::string &lexeme);
        bool isKeyword(const std::string &lexeme);
        bool isOperator(const std::string &lexeme);
        bool isSeparator(const std::string &lexeme);

        /*
        * State-Transition Table
        *
        * Q0 = 0 : Stating State
        * Q = {0, 1, 2} : States
        * F = {2} : Accepting States
        *
        * S | {a-Z} | {0-9} | {_}
        * ------------------------
        * 0 | 2     | 1     | 1
        * 1 | 1     | 1     | 1
        * 2 | 2     | 2     | 2
        * 
        */
        int identifierFSM[3][3] = {
            {2, 1, 1},
            {1, 1, 1},
            {2, 2, 2}
        };
        
        /*
        * State-Transition Table
        *
        * Q0 = 0 : Stating State
        * Q = {0, 1} : States
        * F = {1} : Accepting States
        *
        * S | {0-9}
        * ----------
        * 0 | 1
        * 1 | 1
        * 
        */
        int integerFSM[2][1] = {
            {1},
            {1}
        };

        /*
        * State-Transition Table
        *
        * Q0 = 0 : Stating State
        * Q = {0, 1, 2, 3, 4} : States
        * F = {4} : Accepting States
        *
        * S | {0-9} | {.}
        * ----------------------
        * 0 | 2   | 1
        * 1 | 1   | 1
        * 2 | 2   | 3
        * 3 | 4   | 1
        * 4 | 4   | 1
        *
        */
        int realFSM[5][2] = {
            {2, 1},
            {1, 1},
            {2, 3},
            {4, 1},
            {4, 1},
        };
};
