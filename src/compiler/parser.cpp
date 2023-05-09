#include "parser.h"

Parser::Parser(std::ofstream &outputFile, std::vector<Token> &tokens) : outputFile(outputFile), tokens(tokens) { }

Parser::~Parser() { }

void Parser::parse() {
    itr = tokens.begin();
    token = *itr;
    outputFile << "Token: " + tokenTypeString(token.type) + " Lexeme: " + token.lexeme << std::endl;
    
    procedureR1();

    generator.writeInstructionTableToFile(outputFile);
    generator.writeSymbolTableToFile(outputFile);
}

void Parser::logError(const std::vector<std::string> &expected, const std::string &lexeme, const int &line) {
    std::string message = "Syntax error: Line " + std::to_string(line) + ": Expected ";
    for (auto itr = expected.begin(); itr != expected.end(); itr++) {
        message += "'" + *itr + "'";

        if (std::next(itr) != expected.end()) {
            message += " or ";
        }
    }
    message += " but got '" + lexeme + "'.";

    outputFile << message << std::endl;
    throw std::runtime_error(message);
}

bool Parser::nextToken() {
    if (++itr == tokens.end()) {
        return false;
    }

    token = *itr;
    outputFile << "Token: " + tokenTypeString(token.type) + " Lexeme: " + token.lexeme << std::endl;
    return true;
}

// R1 : <Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>
void Parser::procedureR1() {
    outputFile << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << std::endl;

    procedureR2();

    if (!(token.type == SEPARATOR && token.lexeme == "#")) {
        logError({"#"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR12();

    if (!(token.type == SEPARATOR && token.lexeme == "#")) {
        logError({"#"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR18();
}

// R2 : <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void Parser::procedureR2() {
    outputFile << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "function")) {
        procedureR38();
        return;
    }
    
    procedureR3();
}

// R3 : <Function Definitions> ::= <Function> <Function'>
void Parser::procedureR3() {
    outputFile << "<Function Definitions> ::= <Function> <Function'>" << std::endl;

    procedureR5();
    nextToken();
    procedureR4();
}

// R4 : <Function'> ::= <Empty> | <Function Definitions>
void Parser::procedureR4() {
    outputFile << "<Function'> ::= <Empty> | <Function Definitions>" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "function")) {
        procedureR38();
        return;
    }

    procedureR3();
}

// R5 : <Function> ::= function <Identifier>(<Opt Parameter List>) <Opt Declaration List> <Body>
void Parser::procedureR5() {
    outputFile << "<Function> ::= function <Identifier>(<Opt Parameter List>) <Opt Declaration List> <Body>" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "function")) {
        logError({"function"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == IDENTIFIER)) {
        logError({"identifier"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == "(")) {
        logError({"("}, token.lexeme, token.line);
    }

    nextToken();
    procedureR6();

    if (!(token.type == SEPARATOR && token.lexeme == ")")) {
        logError({")"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR12();

    procedureR11();
}


// R6 : <Opt Parameter List> ::= <Parameter List> | <Empty>
void Parser::procedureR6() {
    outputFile << "<Opt Parameter List> ::= <Parameter List> | <Empty>" << std::endl;

    if (!(token.type == IDENTIFIER)) {
        procedureR38();
        return;
    }
    procedureR7();
}

// R7 : <Parameter List> ::= <Parameter> <Parameter'>
void Parser::procedureR7() {
    outputFile << "<Parameter List> ::= <Parameter> <Parameter'>" << std::endl;
    
    procedureR9();
    nextToken();
    procedureR8();
}

// R8 : <Parameter'> ::= <Empty> | , <Parameter List>
void Parser::procedureR8() {
    outputFile << "<Parameter'> ::= <Empty> | , <Parameter List>" << std::endl;

    if (!(token.type == SEPARATOR && token.lexeme == ",")) {
        procedureR38();
        return;
    }

    nextToken();
    procedureR7();
}

// R9 : <Parameter> ::= <IDs> <Qualifier>
void Parser::procedureR9() {
    outputFile << "<Parameter> ::= <IDs> <Qualifier>" << std::endl;

    procedureR16();
    procedureR10();
}

// R10 : <Qualifier> ::= int | bool | real
void Parser::procedureR10() {
    outputFile << "<Qualifier> ::= int | bool | real" << std::endl;

    if (!(token.type == KEYWORD && (token.lexeme == "int" || token.lexeme == "bool" || token.lexeme == "real"))) {
        logError({"int", "bool", "real"}, token.lexeme, token.line);
    }

    return;
}

// R11 : <Body> ::= { <Statement List> }
void Parser::procedureR11() {
    outputFile << "<Body> ::= { <Statement List> }" << std::endl;

    if (!(token.type == SEPARATOR && token.lexeme == "{")) {
        logError({"{"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR18();

    if (!(token.type == SEPARATOR && token.lexeme == "}")) {
        logError({"}"}, token.lexeme, token.line);
    }
}

// R12 : <Opt Declaration List> ::= <Declaration List> | <Empty>
void Parser::procedureR12() {
    outputFile << "<Opt Declaration List> ::= <Declaration List> | <Empty>" << std::endl;

    if (!(token.type == KEYWORD && (token.lexeme == "int" || token.lexeme == "bool" || token.lexeme == "real"))) {
        procedureR38();
        return;
    }

    procedureR13();
}

// R13 : <Declaration List> ::= <Declaration> ; <Declaration'>
void Parser::procedureR13() {
    outputFile << "<Declaration List> ::= <Declaration> | <Declaration'>" << std::endl;

    procedureR15();
    
    auto queued = generator.getQueuedSymbols();
    for (auto itr = queued.begin(); itr != queued.end(); itr++) {
        generator.insertSymbol(*itr, save.lexeme);
    }
    generator.clearQueuedSymbols();

    if (!(token.type == SEPARATOR && token.lexeme == ";")) {
        logError({";"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR14();
}

// R14 : <Declaration'> ::= <Empty> | <Declaration List>
void Parser::procedureR14() {
    outputFile << "<Declaration'> ::= <Empty> | <Declaration List>" << std::endl;

    if (!(token.type == KEYWORD && (token.lexeme == "int" || token.lexeme == "bool" || token.lexeme == "real"))) {
        procedureR38();
        return;
    }

    procedureR13();
}

// R15 : <Declaration> ::= <Qualifier> <IDs>
void Parser::procedureR15() {
    outputFile << "<Declaration> ::= <Qualifier> <IDs>;" << std::endl;

    procedureR10();
    save = token;

    nextToken();
    procedureR16();
}

// R16 : <IDs> ::= <Identifier> <IDs'>
void Parser::procedureR16() {
    outputFile << "<IDs> ::= <Identifier> <IDs'>" << std::endl;

    if (!(token.type == IDENTIFIER)) {
        logError({"identifier"}, token.lexeme, token.line);
    }
    generator.queueSymbol(token.lexeme);

    nextToken();
    procedureR17();
}

// R17 : <IDs'> ::= <Empty> | , <IDs>
void Parser::procedureR17() {
    outputFile << "<IDs'> ::= <Empty> | , <IDs>" << std::endl;

    if (!(token.type == SEPARATOR && token.lexeme == ",")) {
        procedureR38();
        return;
    }

    nextToken();
    procedureR16();
}

// R18 : <Statement List> ::= <Statement> <Statement'>
void Parser::procedureR18() {
    outputFile << "<Statement List> ::= <Statement> <Statement'>" << std::endl;

    procedureR20();
    if (!nextToken()) {
        return;
    }
    procedureR19();
}

// R19 : <Statement'> ::= <Empty> | <Statement List>
void Parser::procedureR19() {
    outputFile << "<Statement'> ::= <Empty> | <Statement List>" << std::endl;

    if (!((token.type == SEPARATOR && (token.lexeme == "{")) || token.type == IDENTIFIER 
    || (token.type == KEYWORD && (token.lexeme == "if" || token.lexeme == "return" || token.lexeme == "put" || token.lexeme == "get" || token.lexeme == "while")))) {
        if (!((token.type == SEPARATOR && token.lexeme == "}") || (token.type == SEPARATOR && token.lexeme == ";"))) {
            logError({"{", "identifier", "if", "return", "put", "get", "while"}, token.lexeme, token.line);
        }
        procedureR38();
        return;
    }

    procedureR18();
}

// R20 : <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Parser::procedureR20() {
    outputFile << "<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>" << std::endl;

    switch (token.type) {
        case SEPARATOR:
            if (token.lexeme == "{") {
                procedureR21();
            }
            break;
        case IDENTIFIER:
            procedureR22();
            generator.insertInstruction("POPM", generator.getSymbolAddress(save.lexeme));
            break;
        case KEYWORD:
            if (token.lexeme == "if") {
                procedureR23();
            }
            else if (token.lexeme == "return") {
                procedureR25();
            } 
            else if (token.lexeme == "put") {
                procedureR27();
                generator.insertInstruction("OUT", 0);
            } 
            else if (token.lexeme == "get") {
                procedureR28();
                auto queued = generator.getQueuedSymbols();
                for (auto itr = queued.begin(); itr != queued.end(); itr++) {
                    generator.insertInstruction("IN", 0);
                    generator.insertInstruction("POPM", generator.getSymbolAddress(*itr));
                }
                generator.clearQueuedSymbols();
            } 
            else if (token.lexeme == "while") {
                procedureR29();
            }
            break;
        default:
            logError({"{", "<identifier>", "if", "return", "put", "get", "while"}, token.lexeme, token.line);
    }
}

// R21 : <Compound> ::= { <Statement List> }
void Parser::procedureR21() {
    outputFile << "<Compound> ::= { <Statement List> }" << std::endl;

    if (!(token.type == SEPARATOR && token.lexeme == "{")) {
        logError({"{"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR18();

    if (!(token.type == SEPARATOR && token.lexeme == "}")) {
        logError({"}"}, token.lexeme, token.line);
    }
}

// R22 : <Assign> ::= <Identifier> = <Expression> ;
void Parser::procedureR22() {
    outputFile << "<Assign> ::= <Identifier> = <Expression> ;" << std::endl;

    if (!(token.type == IDENTIFIER)) {
        logError({"<identifier>"}, token.lexeme, token.line);
    }
    
    save = token;

    nextToken();
    if (!(token.type == OPERATOR && token.lexeme == "=")) {
        logError({"="}, token.lexeme, token.line);
    }
    
    nextToken();
    procedureR32();

    if (!(token.type == SEPARATOR && token.lexeme == ";")) {
        logError({";"}, token.lexeme, token.line);
    }
}

// R23 : <If> ::= if ( <Condition> ) <Statement> <If'>
void Parser::procedureR23() {
    outputFile << "<If> ::= if ( <Condition> ) <Statement> <If'>" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "if")) {
        logError({"if"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == "(")) {
        logError({"("}, token.lexeme, token.line);
    }

    nextToken();
    procedureR30();

    generator.insertInstruction("JMPZ", 0);
    generator.pushJumpstack();

    if (!(token.type == SEPARATOR && token.lexeme == ")")) {
        logError({")"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR20();

    generator.backPatch();
    generator.insertInstruction("LABEL", 0);

    nextToken();
    procedureR24();
}

// R24 : <If'> ::= fi | else <Statement> fi
void Parser::procedureR24() {
    outputFile << "<If'> ::= fi | else <Statement> fi" << std::endl;

    if (token.type == KEYWORD && token.lexeme == "fi") {
        return;
    }

    if (!(token.type == KEYWORD && token.lexeme == "else")) {
        logError({"else"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR20();

    nextToken();
    if (!(token.type == KEYWORD && token.lexeme == "fi")) {
        logError({"fi"}, token.lexeme, token.line);
    }
}

// R25 : <Return> ::= return <Return'>
void Parser::procedureR25() {
    outputFile << "<Return> ::= return <Return'>" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "return")) {
        logError({"return"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR26();
}

// R26 : <Return'> ::= ; | <Expression> ;
void Parser::procedureR26() {
    outputFile << "<Return'> ::= ; | <Expression> ;" << std::endl;

    if (token.type == SEPARATOR && token.lexeme == ";") {
        return;
    }

    procedureR32();
    
    if (!(token.type == SEPARATOR && token.lexeme == ";")) {
        logError({";"}, token.lexeme, token.line);
    }
}

// R27 : <Print> ::= put ( <Expression> ) ;
void Parser::procedureR27() {
    outputFile << "<Print> ::= put ( <Expression> ) ;" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "put")) {
        logError({"put"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == "(")) {
        logError({"("}, token.lexeme, token.line);
    }

    nextToken();
    procedureR32();

    if (!(token.type == SEPARATOR && token.lexeme == ")")) {
        logError({")"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == ";")) {
        logError({";"}, token.lexeme, token.line);
    }
}

// R28 : <Scan> ::= get ( <IDs> ) ;
void Parser::procedureR28() {
    outputFile << "<Scan> ::= get ( <IDs> ) ;" << std::endl;

    if (!(token.type == KEYWORD && token.lexeme == "get")) {
        logError({"get"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == "(")) {
        logError({"("}, token.lexeme, token.line);
    }

    nextToken();
    procedureR16();

    if (!(token.type == SEPARATOR && token.lexeme == ")")) {
        logError({")"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == ";")) {
        logError({";"}, token.lexeme, token.line);
    }
}

// R29 : <While> ::= while ( <Condition> ) <Statement> endwhile
void Parser::procedureR29() {
    outputFile << "<While> ::= while ( <Condition> ) <Statement> endwhile" << std::endl;

    generator.insertInstruction("LABEL", 0);
    unsigned int labelAddress = generator.getInstructionAddressCounter() - 1;

    if (!(token.type == KEYWORD && token.lexeme == "while")) {
        logError({"while"}, token.lexeme, token.line);
    }

    nextToken();
    if (!(token.type == SEPARATOR && token.lexeme == "(")) {
        logError({"("}, token.lexeme, token.line);
    }

    nextToken();
    procedureR30();

    generator.insertInstruction("JMPZ", 0);
    generator.pushJumpstack();

    if (!(token.type == SEPARATOR && token.lexeme == ")")) {
        logError({")"}, token.lexeme, token.line);
    }

    nextToken();
    procedureR20();

    generator.insertInstruction("JMP", labelAddress);
    generator.backPatch();
    generator.insertInstruction("LABEL", 0);

    nextToken();
    if (!(token.type == KEYWORD && token.lexeme == "endwhile")) {
        logError({"endwhile"}, token.lexeme, token.line);
    }
}

// R30 : <Condition> ::= <Expression> <Relop> <Expression>
void Parser::procedureR30() {
    outputFile << "<Condition> ::= <Expression> <Relop> <Expression>" << std::endl;

    procedureR32();

    Token relop = token;
    procedureR31();

    nextToken();
    procedureR32();
    
    if (relop.lexeme == "==") {
        generator.insertInstruction("EQU", 0);
    }
    else if (relop.lexeme == "!=") {
        generator.insertInstruction("NEQ", 0);
    }
    else if (relop.lexeme == ">") {
        generator.insertInstruction("GRT", 0);
    }
    else if (relop.lexeme == "<") {
        generator.insertInstruction("LES", 0);
    }
    else if (relop.lexeme == "<=") {
        generator.insertInstruction("LEQ", 0);
    }
    else if (relop.lexeme == "=>") {
        generator.insertInstruction("GEQ", 0);
    }
}

// R31 : <Relop> ::= == | != | > | < | <= | =>
void Parser::procedureR31() {
    outputFile << "<Relop> ::= == | != | > | < | <= | =>" << std::endl;

    if (!(token.type == OPERATOR && (token.lexeme == "==" || token.lexeme == "!=" || token.lexeme == ">" || token.lexeme == "<" || token.lexeme == "<=" || token.lexeme == "=>"))) {
        logError({"==", "!=", ">", "<", "<=", "=>"}, token.lexeme, -1);
    }

    return;
}

// R32 : <Expression> ::= <Term> <Expression'>
void Parser::procedureR32() {
    outputFile << "<Expression> ::= <Term> <Expression'>" << std::endl;

    procedureR34();
    procedureR33();
}

// R33 : <Expression'> ::= + <Term> <Expression'> | - <Term> <Expression'> | <Empty>
void Parser::procedureR33() {
    outputFile << "<Expression'> ::= + <Term> <Expression'> | - <Term> <Expression'> | <Empty>" << std::endl;

    if (!(token.type == OPERATOR && (token.lexeme == "+" || token.lexeme == "-"))) {
        procedureR38();
        return;
    }
    bool isAddition = token.lexeme == "+";

    nextToken();
    procedureR34();

    if (isAddition) {
        generator.insertInstruction("ADD", 0);
    }
    else {
        generator.insertInstruction("SUB", 0);
    }

    procedureR33();
}

// R34 : <Term> ::= <Factor> <Term'>
void Parser::procedureR34() {
    outputFile << "<Term> ::= <Factor> <Term'>" << std::endl;

    procedureR36();
    procedureR35();
}

// R35 : <Term'> ::= * <Factor> <Term'> | / <Factor> <Term'> | <Empty>
void Parser::procedureR35() {
    outputFile << "<Term'> ::= * <Factor> <Term'> | / <Factor> <Term'> | <Empty>" << std::endl;

    if (!(token.type == OPERATOR && (token.lexeme == "*" || token.lexeme == "/"))) {
        procedureR38();
        return;
    }
    bool isMultiplication = token.lexeme == "*";

    nextToken();
    procedureR36();

    if (isMultiplication) {
        generator.insertInstruction("MUL", 0);
    }
    else {
        generator.insertInstruction("DIV", 0);
    }

    procedureR35();
}

// R36 : <Factor> ::= - <Primary> | <Primary>
void Parser::procedureR36() {
    outputFile << "<Factor> ::= - <Primary> | <Primary>" << std::endl;

    if (token.type == OPERATOR && token.lexeme == "-") {
        generator.insertInstruction("SUB", 0);
        nextToken();
    }

    procedureR37();
}

// R37 : <Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false
void Parser::procedureR37() {
    outputFile << "<Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false" << std::endl;

    switch (token.type) {
        case IDENTIFIER:
            generator.insertInstruction("PUSHM", generator.getSymbolAddress(token.lexeme));

            nextToken();
            if (!(token.type == SEPARATOR && token.lexeme == "(")) {
                break;
            }

            nextToken();
            procedureR16();

            if (!(token.type == SEPARATOR && token.lexeme == ")")) {
                logError({")"}, token.lexeme, token.line);
            }
            nextToken();

            break;
        case INTEGER:
            generator.insertInstruction("PUSHI", std::stoi(token.lexeme));
            nextToken();
            break;
        case SEPARATOR:
            if (!(token.lexeme == "(")) {
                logError({"("}, token.lexeme, token.line);
            }

            nextToken();
            procedureR32();

            if (!(token.type == SEPARATOR && token.lexeme == ")")) {
                logError({")"}, token.lexeme, token.line);
            }
            nextToken();

            break;
        case REAL:
            nextToken();
            break;
        case KEYWORD:
            if (token.lexeme == "true" || token.lexeme == "false") {
                nextToken();
            }
            break;
        default:
            logError({"<identifier>", "<integer>", "(", "<real>", "true", "false"}, token.lexeme, token.line);
    }
}

// R38 : <Empty> ::= <Empty>
void Parser::procedureR38() {
    outputFile << "<Empty> ::= <Empty>" << std::endl;
    return;
}