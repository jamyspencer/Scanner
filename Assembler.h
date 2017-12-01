//
// Created by jamy on 11/27/17.
//

#ifndef FRONTEND_ASSEMBLER_H
#define FRONTEND_ASSEMBLER_H


#include "Node.h"

class Assembler {

    Node* root;

public:

    Assembler(Node *root);

    void assemble();

private:
    void program();
};


#endif //FRONTEND_ASSEMBLER_H
