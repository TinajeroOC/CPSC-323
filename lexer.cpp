#include "lexer.h"

Lexer::Lexer() {
    
}

Lexer::~Lexer() {

}

void Lexer::tokenize(std::ifstream &input_file) {
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

void Lexer::results(std::ofstream &output_file) {
    std::string test = "Test";
}

bool Lexer::is_identifier(const std::string &lexeme) {
    int state = 0;
    int column = 0;

    for (auto itr = lexeme.begin(); itr != lexeme.end(); itr++) {
        if (state == 1) {
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
            return false;
        case 2:
            return true;
        default:
            return false;
    }
}

bool Lexer::is_integer(const std::string &lexeme) {
    int state = 0;
    int column = 0;

    for (auto itr = lexeme.begin(); itr != lexeme.end(); itr++) {
        if (state == 1) {
            return false;
        }

        if (isdigit(*itr) && *itr == '0') {
            column = 0;
        }
        else if (isdigit(*itr)) {
            column = 1;
        }
        else {
            return false;
        }
        
        state = integerFSM[state][column];
    }

    switch (state) {
        case 0:
            return false;
        case 1:
            return false;
        case 2:
            return true;
        default:
            return false;
    }
}

bool Lexer::is_real(const std::string &lexeme) {    
    int state = 0;
    int column = 0;

    for (auto itr = lexeme.begin(); itr != lexeme.end(); itr++) {
        if (state == 1) {
            return false;   
        }

        if (isdigit(*itr) && *itr == '0') {
            column = 0;
        }
        else if (isdigit(*itr)) {
            column = 1;
        }
        else if (*itr == '.') {
            column = 2;
        }
        else {
            return false;
        }

        state = realFSM[state][column];
    }

    switch (state) {
        case 0:
            return false;
        case 1:
            return false;
        case 2:
            return false;
        case 3:
            return false;
        case 4:
            return true;
        default:
            return false;
    }
}

bool Lexer::is_keyword(const std::string &lexeme) {
    if (keywords.find(lexeme) == keywords.end()) {
        return false;
    }
    return true;
}

bool Lexer::is_operator(const std::string &lexeme) {
    if (operators.find(lexeme) == operators.end()) {
        return false;
    }
    return true;
}

bool Lexer::is_separator(const std::string &lexeme) {
    if (separators.find(lexeme) == separators.end()) {
        return false;
    }
    return true;
}