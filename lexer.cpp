#include "lexer.h"
Lexer::Lexer() {
    
}

Lexer::~Lexer() {
    
}

void Lexer::tokenize(std::ifstream& input_file) {
    bool isComment = false;
    std::string token;
    std::string nextLine;
    std::string separatorHold;
    std::size_t index = 0;
    while (std::getline(input_file, nextLine))
    {
        std::stringstream checker(nextLine);
        while (checker >> token)
        {
            if (token.find("[*") == std::string::npos && isComment != true)
            {
                while (is_separator(token, index))
                {
                    separatorHold = token.substr(index, 1);
                    token.erase(index, 1);
                    //Need to fix, it will go through all separators first.
                    //Need to store separatorHold as a separator token here.
                }
                std::cout << token << std::endl;
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
    int accept[1] = {1};
    for (std::size_t i = 0; i < checkString.length(); i++)
    {
        if (isdigit(checkString[i]))
        {
            if (checkString[i] == '0')
            {
                state = 0;
            }
            else
            {
                state = 1;
            }
        }
        switch(state)
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
    /*  is_integer WITHOUT FSM
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
    */
   return accept[0];
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

bool Lexer::is_separator(std::string lexeme, std::size_t& index) {
    bool exists = false;
    for (const auto& c : separators)
    {
        index = lexeme.find(c);
        if (index != std::string::npos)
        {
            exists = true;
            break;
        }
    }
    return exists;
}