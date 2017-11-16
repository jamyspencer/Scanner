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
    Node* in = new Node(inNode);
    currentToken = scanner.getToken();
    in->insertChild(new Node(identNode, currentToken));
    currentToken = scanner.getToken();
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return in;
}

Node* Parser::out() {
    Node* out = new Node(outNode);
    currentToken = scanner.getToken();
    out->insertChild(expr());
    if (currentToken.id != SEMICOLON_tkn) error(";");
    currentToken = scanner.getToken();
    return out;
}

Node* Parser::check() {
    Node* check = new Node(checkNode, currentToken);
    currentToken = scanner.getToken();
    if (currentToken.id != LEFT_BRACKET_tkn) error("[");
    currentToken = scanner.getToken();
    check->insertChild(expr());
    check->insertChild(RO());
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
    loop->insertChild(RO());
    loop->insertChild(expr());
    if (currentToken.id != RIGHT_BRACKET_tkn) error("]");
    currentToken = scanner.getToken();
    loop->insertChild(stat());
    return loop;
}

Node* Parser::assign() {
    Node* assignment = new Node(assignNode);
    assignment->insertChild(new Node(identNode, currentToken));
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
    if (currentToken.id == PLUS_tkn) {
        expression->insertChild(new Node(plus, currentToken));
        currentToken = scanner.getToken();
        expression->insertChild(expr());
    }
    else if (currentToken.id == MINUS_tkn) {
        expression->insertChild(new Node(minus, currentToken));
        currentToken = scanner.getToken();
        expression->insertChild(expr());
    }
    if (expression->hasChildren()) return expression;
    return nullptr;
}

Node* Parser::M() {
    Node* temp = new Node(MNode);
    temp->insertChild(F());
    if (currentToken.id == PERCENT_tkn){
        Node* newNode = new Node(MNode);
        newNode->insertChild(new Node(percent, currentToken));
        currentToken = scanner.getToken();
        newNode->insertChild(M());
        temp->insertChild(newNode);
    }
    else if (currentToken.id == TIMES_tkn){
        Node* newNode = new Node(MNode);
        newNode->insertChild(new Node(times, currentToken));
        currentToken = scanner.getToken();
        newNode->insertChild(M());
        temp->insertChild(newNode);
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
        temp = new Node(RNode);
        temp->insertChild(new Node(identNode, currentToken));
        currentToken = scanner.getToken();
    }
    else if (currentToken.id == NUM_tkn) {
        temp = new Node(RNode);
        temp->insertChild(new Node(number, currentToken));
        currentToken = scanner.getToken();
    }else{
        error("[ or identifier or number");
    }
    return temp;
}

Node* Parser::RO() {
    switch(currentToken.id){
        Node* temp;
        case LESS_tkn:
            temp =  new Node(less, currentToken);
            currentToken = scanner.getToken();
            return temp;
        case LESS_EQUALS_tkn:
            temp =  new Node(less_equals, currentToken);
            currentToken = scanner.getToken();
            return temp;
        case GREATER_tkn:
            temp =  new Node(greater, currentToken);
            currentToken = scanner.getToken();
            return temp;
        case GREATER_EQUALS_tkn:
            temp =  new Node(greater_equals, currentToken);
            currentToken = scanner.getToken();
            return temp;
        case EQUALS_EQUALS_tkn:
            temp =  new Node(equals_equals, currentToken);
            currentToken = scanner.getToken();
            return temp;
        case NOT_EQUALS_tkn:
            temp =  new Node(not_equals, currentToken);
            currentToken = scanner.getToken();
            return temp;
        default:
            error("'<' or '<=' or '>' or '>=' or '==' or '!='");
    }
    return nullptr;
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
    Node* stats = new Node(statsNode);
    stats->insertChild(stat());
    stats->insertChild(mStat());
    return stats;
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