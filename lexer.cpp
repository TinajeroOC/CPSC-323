#include "lexer.h"
#include <iostream>

Lexer::Lexer() {
    checkSign = 'a';
}

Lexer::~Lexer() {
    
}

void Lexer::tokenize(std::ifstream& input_file) {
    bool isComment = false;
    std::string token;
    std::string nextLine;
    while (std::getline(input_file, nextLine))
    {
        std::stringstream checker(nextLine);
        while (checker >> token)
        {
            if (token.find("[*") == std::string::npos && isComment != true)
            {
                std::cout << token;
                std::cout << std::endl;
            }
            else
            {
                isComment = true;
                if (token.find("*]") != std::string::npos)
                {
                    isComment = false;
                }
            }
        }
    }
}

bool Lexer::validate_tokens() {
    bool valid_token = true;


    return valid_token;
}

int Lexer::signsAndPeriod(char checkSign)
{
    int checkSigns = 0;
    if (isdigit(checkSign))
    {
        checkSigns = 1;
    }
    else if (checkSign == '.')
    {
        checkSigns = 1;
    }
    else if (checkSigns == '+')
    {
        checkSigns = 1;
    }
    else if (checkSigns == '-')
    {
        checkSigns = 1;
    }
    else if (isalpha(checkSign))
    {
        checkSigns = 0;
    }
    return checkSigns;
}

bool Lexer::is_identifier(const std::string &lexeme) {
    int state = 0;
    int column = 0;

    state = 0;
    for (auto itr = lexeme.begin(); itr != lexeme.end(); itr++) {
        if (itr == lexeme.begin() && !(isupper(*itr))) {
            return false;
        }

        if (isalpha(*itr)) {
            column = 0;
        }
        else if (isdigit(*itr)) {
            column = 1;
        }
        else if (*itr == '_') {
            column = 2;
        }
        else {
            return false;
        }

        state = identifierFSM[state][column];
    }

    switch (state) {
        case 0:
            return false;
        case 1:
            return true;
        default:
            return false;
    }
}

bool Lexer::is_real() {    
    return true;
}

bool Lexer::is_integer(std::string checkString) {
    int state = 0;
    int check;
    check = checkString.size();
    for (int i = 0; i < check; i++)
    {
        int column = 0;
        
        if (isdigit(checkString[i]))
        {
            state = 1;
        }
        else
        {
            state = 0;
        }

        switch(state)
        {
            case 0:
                return false;
            case 1:
                state = intFSM[state][column];
        }
    }
    switch (state)
    {
        // If FSM is in state 0 it's not in accepting state so return false.
        case 0:
            return false;
        // If FSM is in state 1 it's an accepting state so return true.
        case 1:
            return true;
    }
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