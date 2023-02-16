#include "lexer.h"

Lexer::Lexer() {}

Lexer::~Lexer() {}

void Lexer::tokenize(std::ifstream &input_file) {
    bool is_comment = false;
    std::string word;
    std::string next_line;
    std::string token_holder;
    std::string previous_token;
    int word_size = 0;

    while (std::getline(input_file, next_line)) {
        std::stringstream checker(next_line);
        while (checker >> word) {
            if (word.find("[*") == std::string::npos && is_comment != true) {
                word_size = word.size();
                for (int i = 0; i < word_size; i++) {
                    if (is_separator(std::string(1, word[i]))) {
                        if (previous_token == "") {
                            Token token = {SEPARATOR, std::string(1, word[i])};
                            tokens.push_back(token);
                        }
                        else {
                            if (is_operator(std::string(previous_token))) {
                                Token token = {OPERATOR, previous_token};
                                tokens.push_back(token);
                            }
                            else if (is_identifier(std::string(previous_token))) {
                                if (is_keyword(std::string(previous_token))) {
                                    Token token = {KEYWORD, previous_token};
                                    tokens.push_back(token);
                                }
                                else {
                                    Token token = {IDENTIFIER, previous_token};
                                    tokens.push_back(token);
                                }
                            }
                            else if (is_integer(std::string(previous_token))) {
                                Token token = {INTEGER, previous_token};
                                tokens.push_back(token);
                            }
                            else if (is_real(std::string(previous_token))) {
                                Token token = {REAL, previous_token};
                                tokens.push_back(token);
                            }
                            else {
                                Token token = {INVALID, previous_token};
                                tokens.push_back(token);
                            }
                            Token token = {SEPARATOR, std::string(1, word[i])};
                            tokens.push_back(token);
                        }
                        previous_token = "";
                        token_holder = "";
                    }
                    else if (is_operator(std::string(1, word[i]))){
                        if (previous_token == "") {
                            Token token = {OPERATOR, std::string(1, word[i])};
                            tokens.push_back(token);
                        }
                        else {
                            if (is_separator(std::string(previous_token))) {
                                Token token = {SEPARATOR, previous_token};
                                tokens.push_back(token);
                            }
                            else if (is_identifier(std::string(previous_token))) {
                                if (is_keyword(std::string(previous_token))) {
                                    Token token = {KEYWORD, previous_token};
                                    tokens.push_back(token);
                                }
                                else {
                                    Token token = {IDENTIFIER, previous_token};
                                    tokens.push_back(token);
                                }
                            }
                            else if (is_integer(std::string(previous_token))) {
                                Token token = {INTEGER, previous_token};
                                tokens.push_back(token);
                            }
                            else if (is_real(std::string(previous_token))) {
                                Token token = {REAL, previous_token};
                                tokens.push_back(token);
                            }
                            else if (is_separator(std::string(1, word[i]))) {
                                Token token = {SEPARATOR, std::string(1, word[i])};
                                tokens.push_back(token);
                            }
                            else
                            {
                                Token token = {INVALID, std::string(1, word[i])};
                                tokens.push_back(token);
                            }
                        }
                        previous_token = "";
                        token_holder = "";
                    }
                    else {
                        token_holder += std::string(1, word[i]);
                        previous_token = token_holder;
                        if (i == word_size-1) {
                            if (is_operator(std::string(token_holder))) {
                                Token token = {OPERATOR, token_holder};
                                tokens.push_back(token);
                            }
                            else if (is_identifier(std::string(previous_token))) {
                                if (is_keyword(std::string(previous_token))) {
                                    Token token = {KEYWORD, previous_token};
                                    tokens.push_back(token);
                                }
                                else {
                                    Token token = {IDENTIFIER, previous_token};
                                    tokens.push_back(token);
                                }
                            }
                            else if (is_integer(std::string(token_holder))) {
                                Token token = {INTEGER, token_holder};
                                tokens.push_back(token);
                            }
                            else if (is_real(std::string(token_holder))) {
                                Token token = {REAL, token_holder};
                                tokens.push_back(token);
                            }
                            else
                            {
                                Token token = {INVALID, std::string(1, word[i])};
                                tokens.push_back(token);
                            }
                        }
                    }
                }
                previous_token = "";
                token_holder = "";
            }
            else {
                is_comment = true;
                if (word.find("*]") != std::string::npos) {
                    is_comment = false;
                }
            }
        }
    }
}

void Lexer::results(std::ofstream &output_file) {
    output_file << "Output:" << std::endl;
    output_file << "-------" << std::endl;
    output_file << std::left << std::setw(18) << "token" << std::right << std::setw(18) << "lexeme" << std::endl;
    output_file << "------------------------------------" << std::endl;

    for (auto itr = tokens.begin(); itr != tokens.end(); itr++) {
        output_file << std::left << std::setw(18) << token_type_str(itr->type) << std::right << std::setw(18) << itr->lexeme << std::endl;
    }
}

std::string Lexer::token_type_str(const TokenType &type) {
    switch (type) {
        case IDENTIFIER:
            return "identifier";
        case INTEGER:
            return "integer";
        case REAL:
            return "real";
        case KEYWORD:
            return "keyword";
        case OPERATOR:
            return "operator";
        case SEPARATOR:
            return "separator";
        case INVALID:
            return "invalid";
    }
    return "ERROR";
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