#include "lexer.h"
Lexer::Lexer() {
    checkSign = 'a';
}

Lexer::~Lexer() {
    
}

void Lexer::tokenize(std::ifstream input_file) {
    bool isComment = false;
    std::string token;
    std::string nextLine;
    std::regex iden("[A-Za-z] [A-Za-z0-9_]*");
    std::regex real("[-]* [0-9]+\\.[0-9]+]");
    std::regex integer("[-]* [0-9]+");
    while (std::getline(input_file, nextLine))
    {
        std::stringstream checker(nextLine);
        while (checker >> token)
        {
            for (int i = 0; i < tokens.size(); i++)
            {
                if (token.find("[*") == -1 && isComment != true)
                {
                    if (regex_match(token, iden))
                    {
                        Token::type = "identifier";
                    }
                    if (regex_match(token, real))
                    {
                        Token::type = "real";
                    }
                    if (regex_match(token, integer))
                    {
                        Token::type = "integer";
                    }
                }
                else
                {
                    isComment = true;
                    if (token.find("*]") != -1)
                    {
                        isComment = false;
                    }
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
    
    

    return true;
}

bool Lexer::is_real() {    
    return true;
}

// Using FSM to determine if the string inputted is an integer or not.
// If the input is an integer, returns true. Else, return false.

int Lexer::signsAndPeriod(char checkSign)
{
    int checkSigns = 0;
    if (isdigit(checkSign))
    {
        checkSigns = 1;
    }
    else if (checkSign == '.')
    {
        checkSigns = 2;
    }
    else if (checkSigns == '+')
    {
        checkSigns = 3;
    }
    else if (checkSigns == '-')
    {
        checkSigns = 4;
    }
    else if (isalpha(checkSign))
    {
        checkSigns = 5;
    }
    else
    {
        checkSigns = 6;
    }
    return checkSigns;
}

bool Lexer::is_integer(std::string checkString) {
    int state = 0;

    for (int i = 0; i < checkString.length(); i++)
    {
        state = intFSM[state][1];
        if (isdigit(checkString[i]))
        {
            if (checkString[i] == '+')
            {
                state = 1;
            }
            else if (checkString[i] == '-')
            {
                state = 1;
            }
            else
            {
                state = 1;
            }
        }
            
            switch (state)
            {
            case 0:
                return false;
            case 1:
                if (i > 0)
                {
                    state = 0;
                }
                else if (checkString.length() < 2)
                {
                    state = 0;
                }
            }

        switch (state)
        {
            case 0:
                return false;
            case 1:
                return true;
        }
    }
    
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