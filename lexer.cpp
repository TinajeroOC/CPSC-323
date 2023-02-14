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

// 
bool Lexer::validate_tokens() {
    bool valid_token = true;


    return valid_token;
}

bool Lexer::is_identifier() {
    bool exists = false;
    
    

    return exists;
}

bool Lexer::is_real() {    
    
    return true;
}

// Using FSM to determine if the string inputted is an integer or not.
// If the input is an integer, returns true. Else, return false.
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