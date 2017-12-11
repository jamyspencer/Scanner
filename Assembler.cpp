//
// Created by jamy on 11/27/17.
//


#include <cstdlib>
#include <cstring>
#include "Assembler.h"
#include "StrFunctions.h"


void Assembler::assemble(Node* root) {
    if (root->children[0]->id == declarationNode){
        declaration(root->children[0]);
        block(root->children[1]);
    }
    else { block(root->children[0]); }
    fprintf(outFile, "\nSTOP\n");
    fprintf(outFile, "ZTEMP0 0\n");
    for (std::set<int>::iterator it = allNumbersUsed.begin(); it != allNumbersUsed.end(); it++){
        fprintf(outFile, "ZTEMP%d 0\n", *it);
    }

}

int Assembler::declaration(Node* node) {

    compileVar var = compileVar();
    strcpy(var.value, node->token.value);
    var.line = node->token.line;
    var.level = currentLevel;

    for (std::vector<compileVar>::iterator it = varStack.begin(); it != varStack.end(); it++){
        if (it->level == currentLevel && equals(it->value, var.value)) {
            printf("ERROR: Duplicate variable declaration: %s on line: %d\n", var.value, var.line);
            exit(1);
        };
    }

    varStack.push_back(var);
    fprintf(outFile, "PUSH\n");
    if (node->children[0] != nullptr){
        return 1 + declaration(node->children[0]);
    }

    return 1;
}

void Assembler::block(Node* node) {
    int varsQuan = 0;
    currentLevel++;
    for (int i = 0; i < 4; i++ ){
        Node* child = node->children[i];
        if (child == nullptr) break;
        switch (child->id){
            case declarationNode: varsQuan = declaration(child); break;
            case statNode: stat(child); break;
        }
    }
    currentLevel--;
    for (int i = 0; i < varsQuan; i++){
        varStack.pop_back();
        fprintf(outFile, "POP\n");
    }
}

void Assembler::expr(Node *node) {
    Node* child = node->children[1];
    if (child == nullptr) {
        child = node->children[0];
        if (child->id == MNode) M(child);
        if (child->id == RNode) R(child);
        if (child->id == FNode) F(child);
    }else{
        if (child->id == exprNode) expr(child);
        else if (child->id == MNode) M(child);
        else if (child->id == FNode) F(child);
        else R(child);
        fprintf(outFile, "STORE ZTEMP0 \n");
        child = node->children[0];
        if (child->id == exprNode) expr(child);
        else if (child->id == MNode) M(child);
        else if (child->id == FNode) F(child);
        else R(child);
        if (node->token.id == PLUS_tkn){
            fprintf(outFile, "ADD ZTEMP0\n");
        }else{
            fprintf(outFile, "SUB ZTEMP0\n");
        }

    }
}

void Assembler::M(Node* node) { //returns stack location of stored value
    Node* child = node->children[1];
    int stackLocation;
    if (child != nullptr){
        if (child->id == exprNode) expr(child);
        else if (child->id == MNode) M(child);
        else if (child->id == RNode) R(child);
        else if (child->id == FNode) F(child);

        fprintf(outFile, "STORE ZTEMP0\n");
    }
    child = node->children[0];
    if (child->id == exprNode) expr(child);
    else if (child->id == MNode) M(child);
    else if (child->id == RNode) R(child);
    else if (child->id == FNode) F(child);
    switch (node->token.id){
        case PERCENT_tkn: fprintf(outFile, "DIV ZTEMP0\n"); break;
        case TIMES_tkn: fprintf(outFile, "MULT ZTEMP0\n"); break;
    }

}


void Assembler::assign(Node *node) {
    Node* child = node->children[0];
    switch (child->id){
        case MNode: M(child); break;
        case exprNode: expr(child); break;
        case RNode: R(child);
    }
    int stackLocation = getStackLocation(std::string(node->token.value));
    fprintf(outFile, "STACKW %d\n", stackLocation);
}

Assembler::~Assembler() {
    fclose(outFile);
}

void Assembler::stat(Node *node) {

    Node* child;
    for (int i = 0; i < 4; i++){
        child = node->children[i];
        if (child == nullptr) break;
        switch (child->id){
            case assignNode: assign(child); break;
            case loopNode: loop(child); break;
            case checkNode: check(child); break;
            case blockNode: block(child); break;
            case outNode: out(child); break;
            case statNode: stat(child); break;
            case inNode: in(child); break;
            case mStatNode: mStat(child); break;
        }
    }
}

void Assembler::R(Node *node) {
    switch (node->token.id) {
        case NUM_tkn:
            fprintf(outFile, "LOAD %s\n", node->token.value);
            break;
        case IDENT_tkn:
            int stackLocation = getStackLocation(std::string(node->token.value));
            fprintf(outFile, "STACKR %d\n", stackLocation);
            fprintf(outFile, "STACKW %d\n", stackLocation);
    }
}

void Assembler::out(Node *node) {
    Node* child = node->children[0];
    switch (child->id){
        case RNode: R(child); break;
        case MNode: M(child); break;
        case FNode: F(child); break;
        case exprNode: expr(child); break;
    }
    fprintf(outFile, "STORE ZTEMP0\n");
    fprintf(outFile, "WRITE ZTEMP0\n");
}

void Assembler::in(Node *node) {
    int stackLocation = getStackLocation(std::string(node->token.value));
    fprintf(outFile, "READ ZTEMP0\n");
    fprintf(outFile, "LOAD ZTEMP0\n");
    fprintf(outFile, "STACKW %d\n", stackLocation);
}

void Assembler::check(Node *node) {
    std::string tempVar = tempVarGen();
    std::string jumpLabel = checkLabelGen();
    fprintf(outFile, "\n");
    //process righthand side
    switch(node->children[1]->id){
        case RNode: R(node->children[1]); break;
        case exprNode: expr(node->children[1]); break;
        case FNode: F(node->children[1]); break;
        case MNode: M(node->children[1]); break;
    }
    //store righthand side in temp var
    fprintf(outFile, "STORE %s\n", tempVar.c_str());

    //process lefthand side
    switch(node->children[0]->id){
        case RNode: R(node->children[0]); break;
        case exprNode: expr(node->children[0]); break;
        case FNode: F(node->children[0]); break;
        case MNode: M(node->children[0]); break;
    }
    //subtract righthand value from lefthand side
    fprintf(outFile, "SUB %s\n", tempVar.c_str());
    switch (node->token.id){
        case EQUALS_EQUALS_tkn:
            fprintf(outFile, "BRPOS %s\nBRNEG %s\n", jumpLabel.c_str(), jumpLabel.c_str());
            break;
        case NOT_EQUALS_tkn:
            fprintf(outFile, "BRZERO %s\n", jumpLabel.c_str());
            break;
        case GREATER_tkn:
            fprintf(outFile, "BRZNEG %s\n", jumpLabel.c_str());
            break;
        case GREATER_EQUALS_tkn:
            fprintf(outFile, "BRNEG %s\n", jumpLabel.c_str());
            break;
        case LESS_tkn:
            fprintf(outFile, "BRZPOS %s\n", jumpLabel.c_str());
            break;
        case LESS_EQUALS_tkn:
            fprintf(outFile, "BRPOS %s\n", jumpLabel.c_str());
            break;
    }
    //process statement
    stat(node->children[2]);

    //tag to jump to on evaluation to false
    fprintf(outFile, "\n%s: NOOP\n", jumpLabel.c_str());
    freeTempVar(tempVar);
}

void Assembler::loop(Node *node) {
    int loopNum = getLoopNum();
    std::string tempVar = tempVarGen();
    fprintf(outFile, "\nLOOPSTART%d: NOOP\n", loopNum);
    //process righthand side
    switch(node->children[1]->id){
        case RNode: R(node->children[1]); break;
        case FNode: F(node->children[1]); break;
        case exprNode: expr(node->children[1]); break;
    }
    //store righthand side in temp var
    fprintf(outFile, "STORE %s\n", tempVar.c_str());

    //process lefthand side
    switch(node->children[0]->id){
        case RNode: R(node->children[0]); break;
        case FNode: F(node->children[0]); break;
        case exprNode: expr(node->children[0]); break;
    }
    //subtract righthand value from lefthand side
    fprintf(outFile, "SUB %s\n", tempVar.c_str());
    //value in accumulator is logical result
    switch (node->token.id){
        case EQUALS_EQUALS_tkn:
            fprintf(outFile, "BRPOS LOOPSTOP%d\nLOOPSTOP%d\n", loopNum, loopNum);
            break;
        case NOT_EQUALS_tkn:
            fprintf(outFile, "BRZERO LOOPSTOP%d\n", loopNum);
            break;
        case GREATER_tkn:
            fprintf(outFile, "BRZNEG LOOPSTOP%d\n", loopNum);
            break;
        case GREATER_EQUALS_tkn:
            fprintf(outFile, "BRNEG LOOPSTOP%d\n", loopNum);
            break;
        case LESS_tkn:
            fprintf(outFile, "BRZPOS LOOPSTOP%d\n", loopNum);
            break;
        case LESS_EQUALS_tkn:
            fprintf(outFile, "BRPOS LOOPSTOP%d\n", loopNum);
            break;
    }
    //process statement
    stat(node->children[2]);
    //jump to beginning of Loop to test conditions
    fprintf(outFile, "BR LOOPSTART%d\n", loopNum);
    fprintf(outFile, "LOOPSTOP%d: NOOP\n", loopNum);
}

void Assembler::mStat(Node *node) {
    stat(node->children[0]);
    if (node->children[1] != nullptr){
        mStat(node->children[1]);
    }
}

//Helper functions

int Assembler::getStackLocation(std::string ident) {
    int val = 0;
    for (int i = varStack.size() - 1; i >= 0; i-- ){
        if (std::string(varStack[i].value) == ident) return val;
        val++;
    }
    printf("ERROR: \"%s\" not declared or out of scope\n", ident.c_str());
    exit(-1);
}

std::string Assembler::tempVarGen() {
    int i = 1;
    while(true){
        if (numbersUsed.find(i) == numbersUsed.end()) break;
        i++;
    }
    numbersUsed.emplace(i);
    allNumbersUsed.emplace(i);
    char buffer[20];
    sprintf(buffer, "ZTEMP%d", i);
    return std::string(buffer);
}

void Assembler::freeTempVar(std::string tempVar){
    std::string numString = tempVar.substr(5);
    int val;
    sscanf(numString.c_str(), "%d", &val);
    numbersUsed.erase(numbersUsed.find(val));
}

std::string Assembler::checkLabelGen() {
    static int checkCount = -1;
    checkCount++;
    char buffer[20];
    sprintf(buffer, "SKIP%d", checkCount);
    return buffer;
}

int Assembler::getLoopNum() {
    static int loopCount = -1;
    loopCount++;
    return loopCount;
}

void Assembler::F(Node *node) {
    Node* child = node->children[0];
    if (child->id == FNode){
        F(child);
        fprintf(outFile, "MULT -1\n");
    }else{
        if (child->id == exprNode) expr(child);
        else if (child->id == MNode) M(child);
        else if (child->id == RNode) R(child);
        else if (child->id == FNode) F(child);
    }
}

Assembler::Assembler(const std::string &fileName) : fileName(fileName) {}
