#include "token.h"

std::string tokenTypeString(const TokenType &type) {
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
        default:
            return "error";
    }
}