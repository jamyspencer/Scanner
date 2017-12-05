//
// Created by jamy on 11/27/17.
//

#ifndef FRONTEND_ASSEMBLER_H
#define FRONTEND_ASSEMBLER_H


#include "Node.h"
#include <string>
#include <stack>
#include <set>

class Assembler {

public:

    Assembler();
    ~Assembler();
    void assemble(Node* root);

private:
    struct compileVar {
        int level = 0;
        char value[10];
        int line;
    };

    int currentLevel = 0;
    std::string fileName = "out.asm";
    FILE* outFile = fopen(fileName.c_str(), "w");
    std::set<int> numbersUsed;
    std::set<int> allNumbersUsed;
    std::vector<compileVar> varStack;
    int declaration(Node* node);
    void assign(Node* node);
    void R(Node* node);
    void M(Node* node);
    void block(Node* node);
    void expr(Node* node);
    void stat(Node* node);
    void mStat(Node* node);
    void out(Node* node);
    void in(Node* node);
    void check(Node* node);
    void loop(Node* node);

    int getStackLocation(std::string ident);
    std::string tempVarGen();
    void freeTempVar(std::string tempVar);
    std::string checkLabelGen();
    int getLoopNum();
};


#endif //FRONTEND_ASSEMBLER_H

/*
- ADD (1, ACC = ACC +arg)
- BR (1, jump to arg)
- BRNEG (1, jump to arg if ACC <0)
- BRZNEG (1, jump to arg if ACC <=0)
- BRPOS (1, jump to arg if ACC >0)
- BRZPOS (1, jump to arg if ACC >=0)
- BRZERO (1, jump to arg if ACC ==0)
- COPY (2, arg1 = arg2)
- DIV (1, ACC = ACC / arg)
- MULT (1, ACC = ACC * arg)
- READ (1, arg=input integer)
- WRITE (1, put arg to output as integer)
- STOP (0, stop program)
- STORE (1, arg = ACC)
- SUB (1, ACC = ACC - arg)
- NOOP (0, nothing)
- LOAD (1, ACC=arg)

ADD, DIV, MULT, WRITE, LOAD, SUB can take either variable or immediate value
as the arg: immediate value is positive integer or negative integer

- PUSH (0, tos++)
- POP (0, tos--)
- STACKW (1,stack[tos-arg]=ACC)
- STACKR (1,ACC=stack[tos-arg])
*/