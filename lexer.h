#pragma once
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <string>

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
    COMMENT,
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Lexer {
    public:
        Lexer();
        ~Lexer();
        void tokenize();
        bool validate_tokens();
        bool is_identifier();
        bool is_integer(std::string checkString);
        bool is_real();
        bool is_keyword(std::string lexeme);
        bool is_operator(std::string lexeme);
        bool is_separator(std::string lexeme);
    private:
        std::queue<Token> tokens;

};