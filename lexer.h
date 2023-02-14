#pragma once
#include <cctype>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <string>
#include <sstream>
#include <regex>
#include <algorithm>

// RAT23S : Keywords
const std::unordered_set<std::string> keywords = {"int", "if", "else", "fi", "while", "endwhile", "return", "get", "put", "bool", "real", "function", "true", "false"};

// RAT23S : Operators
const std::unordered_set<std::string> operators = {"==", "!=", ">", "<", "<=", "=>", "*", "/", "+", "-"};

// RAT23S : Separators
const std::unordered_set<std::string> separators = {"#", "{", "}", "(", ")", ",", ";"};

enum TokenType {
    IDENTIFIER,
    INTEGER,
    REAL,
    KEYWORD,
    OPERATOR,
    SEPARATOR,
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Lexer {
    public:
        Lexer();
        ~Lexer();
        void tokenize(std::ifstream &input_file);
        void results(std::ofstream &output_file);
        bool is_identifier(const std::string &lexeme);
        bool is_integer(const std::string &lexeme);
        bool is_real(const std::string &lexeme);
        bool is_keyword(const std::string &lexeme);
        bool is_operator(const std::string &lexeme);
        bool is_separator(const std::string &lexeme);
    private:
        std::queue<Token> tokens;
        
        /*
        * State-Transition Table
        *
        * Q = {0, 1, 2} : States
        * F = {2} : Accepting States
        *
        * S | {0} | {1-9} 
        * ----------------
        * 0 | 1   | 2
        * 1 | 1   | 1
        * 2 | 2   | 2
        * 
        */
        int integerFSM[3][2] = {
            {0, 2},
            {1, 1},
            {2, 2}
        };

        /*
        * State-Transition Table
        *
        * Q = {0, 1, 2, 3, 4} : States
        * F = {4} : Accepting States
        *
        * S | {0} | {1-9} | {.}
        * ----------------------
        * 0 | 1   | 2     | 1
        * 1 | 1   | 1     | 1 
        * 2 | 2   | 2     | 3
        * 3 | 1   | 4     | 1
        * 4 | 4   | 4     | 4
        *
        */
        int realFSM[5][3] = {
            {1, 2, 1},
            {1, 1, 1},
            {2, 2, 3},
            {1, 4, 1},
            {4, 4, 4}
        };

        /*
        * State-Transition Table
        *
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
};
