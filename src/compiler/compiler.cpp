#include "compiler.h"

Compiler::Compiler() { }

Compiler::~Compiler() { }

void Compiler::run(const std::string &sourceFileName) {
    Lexer lexer;
    std::string inputFilePath = "tests/";
    std::string outputFileName, outputFilePath = "results/";

    std::cout << "Verifying the source file name..." << std::endl;
    if (!hasFileExtension(sourceFileName, "txt")) {
        throw std::runtime_error("ERROR: Source file must have a .txt extension.\n");
    }

    std::cout << "Opening the source file..." << std::endl;
    inputFilePath.append(sourceFileName);
    inputFile.open(inputFilePath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("ERROR: Source file could not be opened.\n");
    }

    std::cout << "Tokenizing the source file..." << std::endl;
    lexer.tokenize(inputFile, tokens);
    
    std::cout << "Opening the results file..." << std::endl;
    outputFileName = getFormattedDate("%m-%d-%Y_%H-%M-%S") + ".txt";
    outputFilePath.append(outputFileName);
    outputFile.open(outputFilePath);
    if (!outputFile.is_open()) {
        throw std::runtime_error("ERROR: Results file could not be opened.\n");
    }
    
    std::cout << "Writing to the results file..." << std::endl;
    results();
    
    std::cout << "Results file: " << outputFileName << std::endl;
    outputFile.close();
    inputFile.close();
}

void Compiler::results() {
    outputFile << "Output:" << std::endl;
    outputFile << "-------" << std::endl;
    outputFile << std::left << std::setw(18) << "token" << std::right << std::setw(18) << "lexeme" << std::endl;
    outputFile << "------------------------------------" << std::endl;

    for (auto itr = tokens.begin(); itr != tokens.end(); itr++) {
        outputFile << std::left << std::setw(18) << tokenTypeString(itr->type) << std::right << std::setw(18) << itr->lexeme << std::endl;
    }
}

std::string Compiler::tokenTypeString(const TokenType &type) {
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

std::string Compiler::getFormattedDate(const std::string &format) {
    time_t rawTime;
    struct tm* timeInfo;
    char timeCStr[500];

    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(timeCStr, 500, format.c_str(), timeInfo);
    
    std::string timestamp(timeCStr);
    
    return timestamp;
}

bool Compiler::hasFileExtension(const std::string &fileName, const std::string &fileExtension) {
    size_t extensionIndex = fileName.find_last_of(".");
    std::string extension = fileName.substr(extensionIndex + 1);
    
    if (extensionIndex == std::string::npos) {
        return false;
    }
    
    if (extension != fileExtension) {
        return false;
    }
    
    return true;
}