//
// Created by jamy on 10/7/17.
//

#include <cstdio>
#include "scannerTester.h"
#include <string>

void Parser::parse() {
    currentToken = scanner.getToken();
    program();

    return;
}

void Parser::program(){
    vars();
    if (currentToken.id != BEGIN_KEYWORD_tkn) error("Begin");
    currentToken = scanner.getToken();
    block();
}

void Parser::block(){
    vars();
    stats();
}

void Parser::stats() {
    stat();
    mStat();
}

void Parser::stat() {
    switch (currentToken.id){
        case INPUT_KEYWORD_tkn:
            currentToken = scanner.getToken();
            in();
            break;
        case OUTPUT_KEYWORD_tkn:
            currentToken = scanner.getToken();
            out();
            break;
        case BEGIN_KEYWORD_tkn:
            currentToken = scanner.getToken();
            out();
            break;
        case CHECK_KEYWORD_tkn:
            currentToken = scanner.getToken();
            check();
            break;
        case LOOP_KEYWORD_tkn:
            currentToken = scanner.getToken();
            loop();
            break;
        case IDENT_tkn:
            currentToken = scanner.getToken();
            assign();
            break;
        default: error("Input or Output or Begin or Check or Loop or identifier");
    }
    return;
}

void Parser::in() {
    if (currentToken.id != IDENT_tkn) error("identifier");
    currentToken = scanner.getToken();
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return;
}

void Parser::out() {
    expr();
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return;
}

void Parser::check() {
    if (currentToken.id != LEFT_BRACKET_tkn) error("[");
    currentToken = scanner.getToken();
    expr();
    RO();
    expr();
    if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
    currentToken = scanner.getToken();
    stat();
    return;
}

void Parser::loop() {
    if (currentToken.id != LEFT_BRACKET_tkn) error("[");
    currentToken = scanner.getToken();
    expr();
    RO();
    expr();
    if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
    currentToken = scanner.getToken();
    stat();
    return;
}

void Parser::assign() {
    if (currentToken.id != COLON_tkn) error(":");
    currentToken = scanner.getToken();
    expr();
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
}

void Parser::expr() {
    M();
    if (currentToken.id == PLUS_tkn) {
        currentToken = scanner.getToken();
        expr();
    }
    else if (currentToken.id == MINUS_tkn) {
        currentToken = scanner.getToken();
        expr();
    }
    return;
}

void Parser::M() {
    F();
    if (currentToken.id == PERCENT_tkn){
        currentToken = scanner.getToken();
        M();
    }
    else if (currentToken.id == TIMES_tkn){
        currentToken = scanner.getToken();
        M();
    }
}

void Parser::F() {
    if (currentToken.id == LEFT_PAREN_tkn){
        currentToken = scanner.getToken();
        F();
        if (currentToken.id != RIGHT_PAREN_tkn) error(")");
    }
    else R();
}

void Parser::R() {
    if (currentToken.id == LEFT_BRACKET_tkn) {
        currentToken = scanner.getToken();
        expr();
        if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
    }
    else if (currentToken.id == IDENT_tkn) currentToken = scanner.getToken();
    else if (currentToken.id == NUM_tkn) currentToken = scanner.getToken();
    else error("[ or identifier or number");
}

void Parser::RO() {
    switch(currentToken.id){
        case LESS_tkn:
        case LESS_EQUALS_tkn:
        case GREATER_tkn:
        case GREATER_EQUALS_tkn:
        case EQUALS_EQUALS_tkn:
        case NOT_EQUALS_tkn:
            currentToken = scanner.getToken();
            break;
        default:
            error("'<' or '<=' or '>' or '>=' or '==' or '!='");
    }
}

void Parser::mStat() {
    switch (currentToken.id){
        case INPUT_KEYWORD_tkn:
        case OUTPUT_KEYWORD_tkn:
        case BEGIN_KEYWORD_tkn:
        case CHECK_KEYWORD_tkn:
        case LOOP_KEYWORD_tkn:
        case IDENT_tkn:
            stat();
            mStat();
            break;
    }
    return;
}

void Parser::vars() {
    if (currentToken.id == VAR_KEYWORD_tkn){
        currentToken = scanner.getToken();
        if (currentToken.id != IDENT_tkn) error("identifier");
        currentToken = scanner.getToken();
        mvars();
    }
    return;
}

void Parser::mvars() {
    if (currentToken.id == COMMA_tkn){
        currentToken = scanner.getToken();
        if (currentToken.id != IDENT_tkn) error("identifier");
        currentToken = scanner.getToken();
        mvars();
    }
    else if (currentToken.id == DOT_tkn){
        currentToken = scanner.getToken();
        return;
    } else{
        error(", or .");
    }
    return;
}

void Parser::error(std::string expected) {
    printf("SYNTAX ERROR: expected %s but received %s at line %d", expected.c_str(), currentToken.value, currentToken.line);
    exit(-1);
}

Parser::Parser(FILE *source_file):
        scanner(Scanner(source_file)){}