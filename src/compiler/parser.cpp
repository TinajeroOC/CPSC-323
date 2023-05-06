#include "parser.h"

Parser::Parser(std::ofstream &outputFile, std::vector<Token> &tokens) : outputFile(outputFile), tokens(tokens) { }

Parser::~Parser() { }

void Parser::parse() {
    this->itr = this->tokens.begin();
    this->token = *this->itr;
    outputFile << "Token: " + tokenTypeString(this->token.type) + " Lexeme: " + this->token.lexeme << std::endl;
    procedureR1();
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
    if (++this->itr == this->tokens.end()) {
        return false;
    }

    this->token = *this->itr;
    outputFile << "Token: " + tokenTypeString(this->token.type) + " Lexeme: " + this->token.lexeme << std::endl;
    return true;
}

// R1 : <Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>
void Parser::procedureR1() {
    outputFile << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << std::endl;

    procedureR2();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == "#")) {
        logError({"#"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR12();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == "#")) {
        logError({"#"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR18();
}

// R2 : <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void Parser::procedureR2() {
    outputFile << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "function")) {
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

    if (!(this->token.type == KEYWORD && this->token.lexeme == "function")) {
        procedureR38();
        return;
    }

    procedureR3();
}

// R5 : <Function> ::= function <Identifier>(<Opt Parameter List>) <Opt Declaration List> <Body>
void Parser::procedureR5() {
    outputFile << "<Function> ::= function <Identifier>(<Opt Parameter List>) <Opt Declaration List> <Body>" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "function")) {
        logError({"function"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == IDENTIFIER)) {
        logError({"identifier"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == "(")) {
        logError({"("}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR6();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
        logError({")"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR12();

    procedureR11();
}


// R6 : <Opt Parameter List> ::= <Parameter List> | <Empty>
void Parser::procedureR6() {
    outputFile << "<Opt Parameter List> ::= <Parameter List> | <Empty>" << std::endl;

    if (!(this->token.type == IDENTIFIER)) {
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

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ",")) {
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

    if (!(this->token.type == KEYWORD && (this->token.lexeme == "int" || this->token.lexeme == "bool" || this->token.lexeme == "real"))) {
        logError({"int", "bool", "real"}, this->token.lexeme, this->token.line);
    }

    return;
}

// R11 : <Body> ::= { <Statement List> }
void Parser::procedureR11() {
    outputFile << "<Body> ::= { <Statement List> }" << std::endl;

    if (!(this->token.type == SEPARATOR && this->token.lexeme == "{")) {
        logError({"{"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR18();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == "}")) {
        logError({"}"}, this->token.lexeme, this->token.line);
    }
}

// R12 : <Opt Declaration List> ::= <Declaration List> | <Empty>
void Parser::procedureR12() {
    outputFile << "<Opt Declaration List> ::= <Declaration List> | <Empty>" << std::endl;

    if (!(this->token.type == KEYWORD && (this->token.lexeme == "int" || this->token.lexeme == "bool" || this->token.lexeme == "real"))) {
        procedureR38();
        return;
    }

    procedureR13();
}

// R13 : <Declaration List> ::= <Declaration> ; <Declaration'>
void Parser::procedureR13() {
    outputFile << "<Declaration List> ::= <Declaration> | <Declaration'>" << std::endl;

    procedureR15();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ";")) {
        logError({";"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR14();
}

// R14 : <Declaration'> ::= <Empty> | <Declaration List>
void Parser::procedureR14() {
    outputFile << "<Declaration'> ::= <Empty> | <Declaration List>" << std::endl;

    if (!(this->token.type == KEYWORD && (this->token.lexeme == "int" || this->token.lexeme == "bool" || this->token.lexeme == "real"))) {
        procedureR38();
        return;
    }

    procedureR13();
}

// R15 : <Declaration> ::= <Qualifier> <IDs>
void Parser::procedureR15() {
    outputFile << "<Declaration> ::= <Qualifier> <IDs>;" << std::endl;

    procedureR10();
    nextToken();
    procedureR16();
}

// R16 : <IDs> ::= <Identifier> <IDs'>
void Parser::procedureR16() {
    outputFile << "<IDs> ::= <Identifier> <IDs'>" << std::endl;

    if (!(this->token.type == IDENTIFIER)) {
        logError({"identifier"}, this->token.lexeme, this->token.line);
    }
    nextToken();
    procedureR17();
}

// R17 : <IDs'> ::= <Empty> | , <IDs>
void Parser::procedureR17() {
    outputFile << "<IDs'> ::= <Empty> | , <IDs>" << std::endl;

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ",")) {
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

    if (!((this->token.type == SEPARATOR && (this->token.lexeme == "{")) || this->token.type == IDENTIFIER 
    || (this->token.type == KEYWORD && (this->token.lexeme == "if" || this->token.lexeme == "return" || this->token.lexeme == "put" || this->token.lexeme == "get" || this->token.lexeme == "while")))) {
        if (!((this->token.type == SEPARATOR && this->token.lexeme == "}") || (this->token.type == SEPARATOR && this->token.lexeme == ";"))) {
            logError({"{", "identifier", "if", "return", "put", "get", "while"}, this->token.lexeme, this->token.line);
        }
        procedureR38();
        return;
    }

    procedureR18();
}

// R20 : <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Parser::procedureR20() {
    outputFile << "<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>" << std::endl;

    switch (this->token.type) {
        case SEPARATOR:
            if (this->token.lexeme == "{") {
                procedureR21();
            }
            break;
        case IDENTIFIER:
            procedureR22();
            break;
        case KEYWORD:
            if (this->token.lexeme == "if") {
                procedureR23();
            } 
            else if (this->token.lexeme == "return") {
                procedureR25();
            } 
            else if (this->token.lexeme == "put") {
                procedureR27();
            } 
            else if (this->token.lexeme == "get") {
                procedureR28();
            } 
            else if (this->token.lexeme == "while") {
                generator.generateInstruction("LABEL", -1);
                procedureR29();
            }
            break;
        default:
            logError({"{", "<identifier>", "if", "return", "put", "get", "while"}, this->token.lexeme, this->token.line);
    }
}

// R21 : <Compound> ::= { <Statement List> }
void Parser::procedureR21() {
    outputFile << "<Compound> ::= { <Statement List> }" << std::endl;

    if (!(this->token.type == SEPARATOR && this->token.lexeme == "{")) {
        logError({"{"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR18();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == "}")) {
        logError({"}"}, this->token.lexeme, this->token.line);
    }
}

// R22 : <Assign> ::= <Identifier> = <Expression> ;
void Parser::procedureR22() {
    outputFile << "<Assign> ::= <Identifier> = <Expression> ;" << std::endl;

    if (!(this->token.type == IDENTIFIER)) {
        logError({"<identifier>"}, this->token.lexeme, this->token.line);
    }
    
    save = token;

    nextToken();
    if (!(this->token.type == OPERATOR && this->token.lexeme == "=")) {
        logError({"="}, this->token.lexeme, this->token.line);
    }

    generator.generateInstruction("POPM", generator.getSymbolAddress(save.lexeme));
    
    nextToken();
    procedureR32();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ";")) {
        logError({";"}, this->token.lexeme, this->token.line);
    }
}

// R23 : <If> ::= if ( <Condition> ) <Statement> <If'>
void Parser::procedureR23() {
    outputFile << "<If> ::= if ( <Condition> ) <Statement> <If'>" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "if")) {
        logError({"if"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == "(")) {
        logError({"("}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR30();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
        logError({")"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    unsigned int jump_address = -1;
    generator.backPatch(jump_address);
    procedureR20();

    nextToken();
    procedureR24();
}

// R24 : <If'> ::= fi | else <Statement> fi
void Parser::procedureR24() {
    outputFile << "<If'> ::= fi | else <Statement> fi" << std::endl;

    if (this->token.type == KEYWORD && this->token.lexeme == "fi") {
        return;
    }

    if (!(this->token.type == KEYWORD && this->token.lexeme == "else")) {
        logError({"else"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR20();

    nextToken();
    if (!(this->token.type == KEYWORD && this->token.lexeme == "fi")) {
        logError({"fi"}, this->token.lexeme, this->token.line);
    }
}

// R25 : <Return> ::= return <Return'>
void Parser::procedureR25() {
    outputFile << "<Return> ::= return <Return'>" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "return")) {
        logError({"return"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR26();
}

// R26 : <Return'> ::= ; | <Expression> ;
void Parser::procedureR26() {
    outputFile << "<Return'> ::= ; | <Expression> ;" << std::endl;

    if (this->token.type == SEPARATOR && this->token.lexeme == ";") {
        return;
    }

    procedureR32();
    
    if (!(this->token.type == SEPARATOR && this->token.lexeme == ";")) {
        logError({";"}, this->token.lexeme, this->token.line);
    }
}

// R27 : <Print> ::= put ( <Expression> ) ;
void Parser::procedureR27() {
    outputFile << "<Print> ::= put ( <Expression> ) ;" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "put")) {
        logError({"put"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == "(")) {
        logError({"("}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR32();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
        logError({")"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == ";")) {
        logError({";"}, this->token.lexeme, this->token.line);
    }
}

// R28 : <Scan> ::= get ( <IDs> ) ;
void Parser::procedureR28() {
    outputFile << "<Scan> ::= get ( <IDs> ) ;" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "get")) {
        logError({"get"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == "(")) {
        logError({"("}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR16();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
        logError({")"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == ";")) {
        logError({";"}, this->token.lexeme, this->token.line);
    }
}

// R29 : <While> ::= while ( <Condition> ) <Statement> endwhile
void Parser::procedureR29() {
    outputFile << "<While> ::= while ( <Condition> ) <Statement> endwhile" << std::endl;

    if (!(this->token.type == KEYWORD && this->token.lexeme == "while")) {
        logError({"while"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    if (!(this->token.type == SEPARATOR && this->token.lexeme == "(")) {
        logError({"("}, this->token.lexeme, this->token.line);
    }

    nextToken();
    procedureR30();

    if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
        logError({")"}, this->token.lexeme, this->token.line);
    }

    nextToken();
    generator.generateInstruction("JMP", generator.getSymbolAddress(save.lexeme));
    unsigned int jump_address = -1;
    generator.backPatch(jump_address);
    procedureR20();

    nextToken();
    if (!(this->token.type == KEYWORD && this->token.lexeme == "endwhile")) {
        logError({"endwhile"}, this->token.lexeme, this->token.line);
    }
}

// R30 : <Condition> ::= <Expression> <Relop> <Expression>
void Parser::procedureR30() {
    outputFile << "<Condition> ::= <Expression> <Relop> <Expression>" << std::endl;

    procedureR32();
    procedureR31();
    nextToken();
    procedureR32();
}

// R31 : <Relop> ::= == | != | > | < | <= | =>
void Parser::procedureR31() {
    outputFile << "<Relop> ::= == | != | > | < | <= | =>" << std::endl;

    if (this->token.lexeme == "==") {
        generator.generateInstruction("EQU", NULL);
    }
    else if (this->token.lexeme == "!=") {
        generator.generateInstruction("NEQ", NULL);
    }
    else if (this->token.lexeme == ">") {
        generator.generateInstruction("GRT", NULL);
    }
    else if (this->token.lexeme == "<") {
        generator.generateInstruction("LES", NULL);
    }
    else if (this->token.lexeme == "<=") {
        generator.generateInstruction("LEQ", NULL);
    }
    else if (this->token.lexeme == "=>") {
        generator.generateInstruction("GEQ", NULL);
    }    
    else {
        logError({"==", "!=", ">", "<", "<=", "=>"}, this->token.lexeme, this->token.line);
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

    if (!(this->token.type == OPERATOR && (this->token.lexeme == "+" || this->token.lexeme == "-"))) {
        procedureR38();
        return;
    }

    save = token;

    if (this->token.lexeme == "+") {
        generator.generateInstruction("ADD", -1);
    }
    else if (this->token.lexeme == "-") {
        generator.generateInstruction("SUB", -1);
    }

    nextToken();
    procedureR34();
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

    if (!(this->token.type == OPERATOR && (this->token.lexeme == "*" || this->token.lexeme == "/"))) {
        procedureR38();
        return;
    }

    if (this->token.lexeme == "*") {
        generator.generateInstruction("MUL", -1);
    }
    else if (this->token.lexeme == "/") {
        generator.generateInstruction("DIV", -1);
    }

    nextToken();
    procedureR36();
    procedureR35();
}

// R36 : <Factor> ::= - <Primary> | <Primary>
void Parser::procedureR36() {
    outputFile << "<Factor> ::= - <Primary> | <Primary>" << std::endl;

    if (this->token.type == OPERATOR && this->token.lexeme == "-") {
        generator.generateInstruction("SUB", -1);
        nextToken();
    }

    

    procedureR37();
}

// R37 : <Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false
void Parser::procedureR37() {
    outputFile << "<Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false" << std::endl;

    switch (this->token.type) {
        case IDENTIFIER:
            nextToken();
            if (!(this->token.type == SEPARATOR && this->token.lexeme == "(")) {
                break;
            }

            nextToken();
            procedureR16();

            if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
                logError({")"}, this->token.lexeme, this->token.line);
            }
            nextToken();

            break;
        case INTEGER:
            nextToken();
            break;
        case SEPARATOR:
            if (!(this->token.lexeme == "(")) {
                logError({"("}, this->token.lexeme, this->token.line);
            }

            nextToken();
            procedureR32();

            if (!(this->token.type == SEPARATOR && this->token.lexeme == ")")) {
                logError({")"}, this->token.lexeme, this->token.line);
            }
            nextToken();

            break;
        case REAL:
            nextToken();
            break;
        case KEYWORD:
            if (this->token.lexeme == "true" || this->token.lexeme == "false") {
                nextToken();
            }
            break;
        default:
            logError({"<identifier>", "<integer>", "(", "<real>", "true", "false"}, this->token.lexeme, this->token.line);
    }
}

// R38 : <Empty> ::= <Empty>
void Parser::procedureR38() {
    outputFile << "<Empty> ::= <Empty>" << std::endl;
    return;
}