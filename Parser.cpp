//
// Created by jamy on 10/7/17.
//

#include <cstdio>
#include "Parser.h"
#include "Node.h"
#include <string>

Node* Parser::parse() {
    currentToken = scanner.getToken();
    Node* node = program();

    return node;
}

Node* Parser::program(){
    Node* program = new Node(programNode);
    program->insertChild(vars());
    if (currentToken.id != BEGIN_KEYWORD_tkn) error("Begin");
    currentToken = scanner.getToken();
    program->insertChild(block());
    return program;
}

Node* Parser::block(){
    Node* block = new Node(blockNode);
    block->insertChild(vars());
    block->insertChild(stats());
    if (currentToken.id != END_KEYWORD_tkn) error("End");
    currentToken = scanner.getToken();
    return block;
}


Node* Parser::in() {
    currentToken = scanner.getToken();
    if (currentToken.id != IDENT_tkn) error("identifier");
    Node* in = new Node(inNode, currentToken);
    currentToken = scanner.getToken();
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return in;
}

Node* Parser::out() {
    currentToken = scanner.getToken();
    Node* out = new Node(outNode);
    out->insertChild(expr());
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return out;
}

Node* Parser::check() {
    Node* check = new Node(checkNode);
    currentToken = scanner.getToken();
    if (currentToken.id != LEFT_BRACKET_tkn) error("[");
    currentToken = scanner.getToken();
    check->insertChild(expr());
    check->token = RO();
    check->insertChild(expr());
    if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
    currentToken = scanner.getToken();
    check->insertChild(stat());
    return check;
}

Node* Parser::loop() {
    Node* loop = new Node(loopNode);
    currentToken = scanner.getToken();
    if (currentToken.id != LEFT_BRACKET_tkn) error("[");
    currentToken = scanner.getToken();
    loop->insertChild(expr());
    loop->token = RO();
    loop->insertChild(expr());
    if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
    currentToken = scanner.getToken();
    loop->insertChild(stat());
    return loop;
}

Node* Parser::assign() {

    Node* assignment = new Node(assignNode, currentToken);
    currentToken = scanner.getToken();
    if (currentToken.id != COLON_tkn) error(":");
    currentToken = scanner.getToken();
    assignment->insertChild(expr());
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return assignment;
}

Node* Parser::expr() {
    Node* expression = new Node(exprNode);
    expression->insertChild(M());
    if (currentToken.id == PLUS_tkn || currentToken.id == MINUS_tkn){
        expression->token = currentToken;
        currentToken = scanner.getToken();
        expression->insertChild(expr());
    }

    if (expression->hasChildren()) return expression;
    return nullptr;
}

Node* Parser::M() {
    Node* temp = new Node(MNode);
    temp->insertChild(F());
    if (currentToken.id == PERCENT_tkn || currentToken.id == TIMES_tkn){
        temp->token = currentToken;
        currentToken = scanner.getToken();
        temp->insertChild(M());
    }

    if (temp->hasChildren()) return temp;
    return nullptr;
}

Node* Parser::F() {
    Node* temp = new Node(FNode);
    if (currentToken.id == LEFT_PAREN_tkn){
        currentToken = scanner.getToken();
        F();
        if (currentToken.id != RIGHT_PAREN_tkn) error(")");
        currentToken = scanner.getToken();
    }else{
        temp->insertChild(R());
    }
    if (temp->hasChildren()) return temp;
    return nullptr;
}

Node* Parser::R() {
    Node* temp = nullptr;
    if (currentToken.id == LEFT_BRACKET_tkn) {
        temp = new Node(RNode);
        currentToken = scanner.getToken();
        temp->insertChild(expr());
        if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
        currentToken = scanner.getToken();
    }
    else if (currentToken.id == IDENT_tkn) {
        temp = new Node(RNode, currentToken);
        currentToken = scanner.getToken();
    }
    else if (currentToken.id == NUM_tkn) {
        temp = new Node(RNode, currentToken);
        currentToken = scanner.getToken();
    }else{
        error("[ or identifier or number");
    }
    return temp;
}

token Parser::RO() {
    token temp;
    switch(currentToken.id){
        case LESS_tkn:
        case LESS_EQUALS_tkn:
        case GREATER_tkn:
        case GREATER_EQUALS_tkn:
        case EQUALS_EQUALS_tkn:
        case NOT_EQUALS_tkn:
            temp = currentToken;
            currentToken = scanner.getToken();
            return temp;
        default:
            error("'<' or '<=' or '>' or '>=' or '==' or '!='");
    }
    return token();
}

Node* Parser::mStat() {
    switch (currentToken.id){
        case INPUT_KEYWORD_tkn:
        case OUTPUT_KEYWORD_tkn:
        case BEGIN_KEYWORD_tkn:
        case CHECK_KEYWORD_tkn:
        case LOOP_KEYWORD_tkn:
        case IDENT_tkn:
            Node* node = new Node(mStatNode);
            node->insertChild(stat());
            node->insertChild(mStat());
            return node;
    }
    return nullptr;
}

Node* Parser::stats() {
    Node* r_stat = stat();
    r_stat->insertChild(mStat());
    return r_stat;
}

Node* Parser::stat() {
    Node* stat = new Node(statNode);
    switch (currentToken.id){
        case INPUT_KEYWORD_tkn:
            stat->insertChild(in());
            return stat;
        case OUTPUT_KEYWORD_tkn:
            stat->insertChild(out());
            return stat;
        case BEGIN_KEYWORD_tkn:
            currentToken = scanner.getToken();
            stat->insertChild(block());
            return stat;
        case CHECK_KEYWORD_tkn:
            stat->insertChild(check());
            return stat;
        case LOOP_KEYWORD_tkn:
            stat->insertChild(loop());
            return stat;
        case IDENT_tkn:
            stat->insertChild(assign());
            return stat;
        default: error("Input or Output or Begin or Check or Loop or identifier");
    }
    return nullptr;
}

Node* Parser::vars() {
    Node* vars = nullptr;
    if (currentToken.id == VAR_KEYWORD_tkn){
        currentToken = scanner.getToken();
        if (currentToken.id != IDENT_tkn) error("identifier");
        vars =  new Node(declarationNode, currentToken);
        currentToken = scanner.getToken();
        vars->insertChild(mvars());
    }
    return vars;
}

Node* Parser::mvars() {
    Node* vars = nullptr;
    if (currentToken.id == DOT_tkn) {
        currentToken = scanner.getToken();
        return nullptr;
    }
    if (currentToken.id == COMMA_tkn){
        currentToken = scanner.getToken();
        if (currentToken.id != IDENT_tkn) error("identifier");
        vars =  new Node(declarationNode, currentToken);
        currentToken = scanner.getToken();
        vars->insertChild(mvars());
        return vars;
    }
    error(", or .");

    return nullptr;
}

void Parser::error(std::string expected) {
    printf("SYNTAX ERROR: expected %s but received %s at line %d", expected.c_str(), currentToken.value, currentToken.line);
    exit(-1);
}

Parser::Parser(FILE *source_file):
        scanner(Scanner(source_file)){}