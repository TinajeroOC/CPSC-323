#pragma once
#include <string>

enum TokenType {
    IDENTIFIER,
    INTEGER,
    REAL,
    KEYWORD,
    OPERATOR,
    SEPARATOR,
    INVALID,
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token& operator=(const Token &rhs) {
        type = rhs.type;
        lexeme = rhs.lexeme;
        line = rhs.line;
        return *this;
    }
};

std::string tokenTypeString(const TokenType &type);