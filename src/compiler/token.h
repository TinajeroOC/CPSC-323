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
};

std::string tokenTypeString(const TokenType &type);