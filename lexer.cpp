#include "lexer.h"

Lexer::Lexer() {
    
}

Lexer::~Lexer() {
    
}

void Lexer::tokenize() {
    
}

bool Lexer::validate_tokens() {
    return true;
}

bool Lexer::is_identifier() {
    return true;
}

bool Lexer::is_real() {    
    return true;
}

bool Lexer::is_integer() {
    return true;
}
// Checks if the keyword given is part of the list of keywords
bool Lexer::is_keyword(std::string lexeme) {
    bool exists = false;
    std::unordered_set<std::string>::const_iterator finder = keywords.find(lexeme);
    if (finder == keywords.end())
    {
        exists = true;
    }
    return exists;
}

bool Lexer::is_operator(std::string lexeme) {
    bool exists = false;
    std::unordered_set<std::string>::const_iterator finder = operators.find(lexeme);
    if (finder == operators.end())
    {
        exists = true;
    }
    return exists;
}

bool Lexer::is_separator(std::string lexeme) {
    bool exists = false;
    std::unordered_set<std::string>::const_iterator finder = separators.find(lexeme);
    if (finder == separators.end())
    {
        exists = true;
    }
    return exists;
}