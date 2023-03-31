#include "lexer.h"

Lexer::Lexer(std::ifstream &inputFile, std::ofstream &outputFile, std::vector<Token> &tokens) : inputFile(inputFile), outputFile(outputFile), tokens(tokens) { }

Lexer::~Lexer() { }

void Lexer::tokenize() {
    bool isComment = false;
    std::string word;
    std::string nextLine;
    std::string tokenHolder;
    std::string previousToken;
    std::string cases;
    int wordSize = 0;
    int line = 0;

    while (std::getline(inputFile, nextLine)) {
        std::stringstream checker(nextLine);
        line++;
        while (checker >> word) {
            if (word.find("[*") == std::string::npos && isComment != true) {
                wordSize = word.size();
                for (int i = 0; i < wordSize; i++) {
                    if (isSeparator(std::string(1, word[i]))) {
                        if (previousToken == "") {
                            Token token = {SEPARATOR, std::string(1, word[i]), line};
                            tokens.push_back(token);
                        }
                        else {
                            std::transform(previousToken.begin(), previousToken.end(), previousToken.begin(), ::tolower);
                            if (isOperator(previousToken)) {
                                Token token = {OPERATOR, previousToken, line};
                                tokens.push_back(token);
                            }
                            else if (isIdentifier(previousToken)) {
                                if (isKeyword(previousToken)) {
                                    Token token = {KEYWORD, cases, line};
                                    tokens.push_back(token);
                                }
                                else {
                                    Token token = {IDENTIFIER, cases, line};
                                    tokens.push_back(token);
                                }
                            }
                            else if (isInteger(previousToken)) {
                                Token token = {INTEGER, previousToken, line};
                                tokens.push_back(token);
                            }
                            else if (isReal(previousToken)) {
                                Token token = {REAL, previousToken, line};
                                tokens.push_back(token);
                            }
                            else {
                                Token token = {INVALID, previousToken, line};
                                tokens.push_back(token);
                            }
                            Token token = {SEPARATOR, std::string(1, word[i]), line};
                            tokens.push_back(token);
                        }
                        previousToken = "";
                        tokenHolder = "";
                    }
                    else if (isOperator(std::string(1, word[i]))) {
                        if (previousToken == "") {
                            if (std::string(1, word[i]) == "=") {
                                if (std::string(1, word[i+1]) == "=") {
                                    tokenHolder = "==";
                                    Token token = {OPERATOR, tokenHolder, line};
                                    tokens.push_back(token);
                                    i++;
                                }
                                else if (std::string(1, word[i+1]) == ">") {
                                    tokenHolder = "=>";
                                    Token token = {OPERATOR, tokenHolder, line};
                                    tokens.push_back(token);
                                    i++;
                                }
                                else {
                                    tokenHolder = "=";
                                    Token token = {OPERATOR, tokenHolder, line};
                                    tokens.push_back(token);
                                }
                            }
                            else if (std::string(1, word[i]) == "!") {
                                if (std::string(1, word[i+1]) == "=") {
                                    tokenHolder = "!=";
                                    Token token = {OPERATOR, tokenHolder, line};
                                    tokens.push_back(token);
                                    i++;
                                }
                                else {
                                    Token token = {INVALID, std::string(1, word[i]), line};
                                    tokens.push_back(token);
                                }
                            }
                            else if (std::string(1, word[i]) == "<") {
                                if (std::string(1, word[i+1]) == "=") {
                                    tokenHolder = "<=";
                                    Token token = {OPERATOR, tokenHolder, line};
                                    tokens.push_back(token);
                                    i++;
                                }
                                else {
                                    Token token = {OPERATOR, std::string(1, word[i]), line};
                                    tokens.push_back(token);
                                }
                            }
                            else {
                                Token token = {OPERATOR, std::string(1, word[i]), line};
                                tokens.push_back(token);
                            }
                        }
                        else {
                            cases = previousToken;
                            std::transform(previousToken.begin(), previousToken.end(), previousToken.begin(), ::tolower);
                            if (isSeparator(previousToken)) {
                                Token token = {SEPARATOR, previousToken, line};
                                tokens.push_back(token);
                            }
                            else if (isIdentifier(previousToken)) {
                                if (isKeyword(previousToken)) {
                                    Token token = {KEYWORD, cases, line};
                                    tokens.push_back(token);
                                }
                                else {
                                    Token token = {IDENTIFIER, cases, line};
                                    tokens.push_back(token);
                                }
                            }
                            else if (isInteger(previousToken)) {
                                Token token = {INTEGER, previousToken, line};
                                tokens.push_back(token);
                            }
                            else if (isReal(previousToken)) {
                                Token token = {REAL, previousToken, line};
                                tokens.push_back(token);
                            }
                            else if (isSeparator(std::string(1, word[i]))) {
                                Token token = {SEPARATOR, std::string(1, word[i]), line};
                                tokens.push_back(token);
                            }
                            else if (isOperator(std::string(1, word[i]))) {
                                if (std::string(1, word[i]) == "=") {
                                    if (std::string(1, word[i+1]) == "=") {
                                        tokenHolder = "==";
                                        Token token = {OPERATOR, tokenHolder, line};
                                        tokens.push_back(token);
                                        i++;
                                    }
                                }
                                else if (std::string(1, word[i]) == "!") {
                                    if (std::string(1, word[i+1]) == "=") {
                                        tokenHolder = "!=";
                                        Token token = {OPERATOR, tokenHolder, line};
                                        tokens.push_back(token);
                                        i++;
                                    }
                                    else {
                                        Token token = {INVALID, std::string(1, word[i]), line};
                                        tokens.push_back(token);
                                    }
                                }
                                else if (std::string(1, word[i]) == "<") {
                                    if (std::string(1, word[i+1]) == "=") {
                                        tokenHolder = "<=";
                                        Token token = {OPERATOR, tokenHolder, line};
                                        tokens.push_back(token);
                                        i++;
                                    }
                                    else {
                                        Token token = {OPERATOR, std::string(1, word[i]), line};
                                        tokens.push_back(token);
                                    }
                                }
                                else {
                                    Token token = {OPERATOR, tokenHolder, line};
                                    tokens.push_back(token);
                                }
                            }
                            else {
                                Token token = {INVALID, std::string(1, word[i]), line};
                                tokens.push_back(token);
                            }
                            Token token = {OPERATOR, std::string(1, word[i]), line};
                            tokens.push_back(token);
                        }
                        previousToken = "";
                        tokenHolder = "";
                    }
                    else {
                        tokenHolder += std::string(1, word[i]);
                        previousToken = tokenHolder;
                        cases = previousToken;
                        std::transform(previousToken.begin(), previousToken.end(), previousToken.begin(), ::tolower);
                        if (std::string(1, word[i]) == "!") {
                            if (std::string(1, word[i+1]) == "=") {
                                tokenHolder = "!=";
                                Token token = {OPERATOR, tokenHolder, line};
                                tokens.push_back(token);
                                i = i + 2;
                            }
                            else {
                                Token token = {INVALID, std::string(1, word[i]), line};
                                tokens.push_back(token);
                            }
                        }
                        if (i == wordSize-1) {
                            if (isOperator(tokenHolder)) {
                                Token token = {OPERATOR, tokenHolder, line};
                                tokens.push_back(token);
                            }
                            else if (isIdentifier(previousToken)) {
                                if (isKeyword(previousToken)) {
                                    Token token = {KEYWORD, cases, line};
                                    tokens.push_back(token);
                                }
                                else {
                                    Token token = {IDENTIFIER, cases, line};
                                    tokens.push_back(token);
                                }
                            }
                            else if (isInteger(tokenHolder)) {
                                Token token = {INTEGER, tokenHolder, line};
                                tokens.push_back(token);
                            }
                            else if (isReal(tokenHolder)) {
                                Token token = {REAL, tokenHolder, line};
                                tokens.push_back(token);
                            }
                            else
                            {
                                Token token = {INVALID, tokenHolder, line};
                                tokens.push_back(token);
                            }
                        }
                    }
                }
                previousToken = "";
                tokenHolder = "";
            }
            else {
                isComment = true;
                if (word.find("*]") != std::string::npos) {
                    isComment = false;
                }
            }
        }
    }
}

void Lexer::writeTokensToFile() {
    outputFile << "Output:" << std::endl;
    outputFile << "-------" << std::endl;
    outputFile << std::left << std::setw(18) << "token" << std::right << std::setw(18) << "lexeme" << std::endl;
    outputFile << "------------------------------------" << std::endl;

    for (auto itr = tokens.begin(); itr != tokens.end(); itr++) {
        outputFile << std::left << std::setw(18) << tokenTypeString(itr->type) << std::right << std::setw(18) << itr->lexeme << std::endl;
    }

    outputFile << "------------------------------------" << std::endl;
}

bool Lexer::isIdentifier(const std::string &lexeme) {
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

bool Lexer::isInteger(const std::string &lexeme) {
    int state = 0;
    int column = 0;

    for (auto itr = lexeme.begin(); itr != lexeme.end(); itr++) {
        if (isdigit(*itr)) {
            column = 0;
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
            return true;
        default:
            return false;
    }
}

bool Lexer::isReal(const std::string &lexeme) {    
    int state = 0;
    int column = 0;

    for (auto itr = lexeme.begin(); itr != lexeme.end(); itr++) {
        if (state == 1) {
            return false;   
        }

        if (isdigit(*itr)) {
            column = 0;
        }
        else if (*itr == '.') {
            column = 1;
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

bool Lexer::isKeyword(const std::string &lexeme) {
    if (keywords.find(lexeme) == keywords.end()) {
        return false;
    }
    return true;
}

bool Lexer::isOperator(const std::string &lexeme) {
    if (operators.find(lexeme) == operators.end()) {
        return false;
    }
    return true;
}

bool Lexer::isSeparator(const std::string &lexeme) {
    if (separators.find(lexeme) == separators.end()) {
        return false;
    }
    return true;
}