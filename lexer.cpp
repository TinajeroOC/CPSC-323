#include "lexer.h"

Lexer::Lexer() {
    
}

Lexer::~Lexer() {

}

void Lexer::tokenize(std::ifstream &input_file) {
    bool isComment = false;
    std::string word;
    std::string nextLine;
    std::string tokenHolder;
    std::string prevToken;
    int wordSize = 0;
    while (std::getline(input_file, nextLine))
    {
        std::stringstream checker(nextLine);
        while (checker >> word)
        {
            if (word.find("[*") == std::string::npos && isComment != true)
            {
                wordSize = word.size();
                for (int i = 0; i < wordSize; i++)
                {
                    if (is_separator(std::string(1, word[i])))
                    {
                        if (prevToken == "")
                        {
                            std::cout << "Separator: " << std::string(1, word[i]) << std::endl;
                            Token token = {SEPARATOR, std::string(1, word[i])};
                            tokens.push(token);
                        }
                        else
                        {
                            if (is_operator(std::string(prevToken)))
                            {
                                std::cout << "Operator: " << prevToken << std::endl;
                                Token token = {SEPARATOR, prevToken};
                                tokens.push(token);
                            }
                            if (is_identifier(std::string(prevToken)))
                            {
                                if (is_keyword(std::string(prevToken)))
                                {
                                    std::cout << "Keyword: " << prevToken << std::endl;
                                    Token token = {KEYWORD, prevToken};
                                    tokens.push(token);
                                }
                                else
                                {
                                    std::cout << "Identifier: " << prevToken << std::endl;
                                    Token token = {IDENTIFIER, prevToken};
                                    tokens.push(token);
                                }
                            }
                            if (is_integer(std::string(prevToken)))
                            {
                                std::cout << "Integer: " << prevToken << std::endl;
                                Token token = {INTEGER, prevToken};
                                tokens.push(token);
                            }
                            if (is_real(std::string(prevToken)))
                            {
                                std::cout << "Real: " << prevToken << std::endl;
                                Token token = {REAL, prevToken};
                                tokens.push(token);
                            }
                            if (is_separator(std::string(1, word[i])))
                            {
                                std::cout << "Separator: " << std::string(1, word[i]) << std::endl;
                                Token token = {SEPARATOR, std::string(1, word[i])};
                                tokens.push(token);
                            }
                        }
                        prevToken = "";
                        tokenHolder = "";
                    }
                    else
                    {
                        tokenHolder += std::string(1, word[i]);
                        prevToken = tokenHolder;
                        if (i == wordSize-1)
                        {
                            if (is_operator(std::string(tokenHolder)))
                            {
                                std::cout << "Operator: " << tokenHolder << std::endl;
                                Token token = {SEPARATOR, tokenHolder};
                                tokens.push(token);
                            }
                            if (is_identifier(std::string(prevToken)))
                            {
                                if (is_keyword(std::string(prevToken)))
                                {
                                    std::cout << "Keyword: " << prevToken << std::endl;
                                    Token token = {KEYWORD, prevToken};
                                    tokens.push(token);
                                }
                                else
                                {
                                    std::cout << "Identifier: " << prevToken << std::endl;
                                    Token token = {IDENTIFIER, prevToken};
                                    tokens.push(token);
                                }
                            }
                            if (is_integer(std::string(tokenHolder)))
                            {
                                std::cout << "Integer: " << tokenHolder << std::endl;
                                Token token = {INTEGER, tokenHolder};
                                tokens.push(token);
                            }
                            if (is_real(std::string(tokenHolder)))
                            {
                                std::cout << "Real: " << tokenHolder << std::endl;
                                Token token = {REAL, tokenHolder};
                                tokens.push(token);
                            }
                        }
                    }
                }
                prevToken = "";
                tokenHolder = "";
            }
            else
            {
                isComment = true;
                if (word.find("*]") != std::string::npos)
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