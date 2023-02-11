#include "lexer.h"

Lexer::Lexer() {
    
}

Lexer::~Lexer() {
    
}

void Lexer::tokenize() {
    
}

// 
bool Lexer::validate_tokens() {
    bool valid_token = true;


    return valid_token;
}

bool Lexer::is_identifier() {
    bool exists = false;
    
    

    return true;
}

bool Lexer::is_real() {    
    return true;
}

// Using FSM to determine if the string inputted is an integer or not.
// If the input is an integer, returns true. Else, return false.
bool Lexer::is_integer(std::string checkString) {
    bool isInteger = false;
    int checkSign = 0;

    if (checkString.length() == 0)
    {
        return false;
    }
    for (int i = 0; i < checkString.length(); i++)
    {
        // Checks the signs of integer since -10 and +10 are integers.
        if (checkString[i] == '-' || checkString[i] == '+')
        {
            checkSign = 1;
        }

        switch(checkSign)
        {
            case 0:
            if (isdigit(checkString[i]))
            {
                isInteger = true;
            }
            else
            {
                return false;
            }

            case 1:
            if (i > 0)
            {
                return false;
            }
            else if (checkString.length() < 2)
            {
                return false;
            }
        }
    }

    
    return isInteger;
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