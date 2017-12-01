//
// Created by jamy on 11/27/17.
//

#ifndef FRONTEND_ASSEMBLER_H
#define FRONTEND_ASSEMBLER_H


#include "Node.h"
#include <string>
#include <stack>

class Assembler {

    Node* root;

public:

    Assembler(Node *root);

    void assemble();

private:
    std::stack<token> varStack;
    void program();
    void declaration(Node* node);
    void block(Node* node);
    void expr(Node* node);

    int getStackLocation(std::string ident);
};


#endif //FRONTEND_ASSEMBLER_H
