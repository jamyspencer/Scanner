//
// Created by jamy on 11/27/17.
//

#include "Assembler.h"

Assembler::Assembler(Node *root) : root(root) {}

void Assembler::assemble() {
    program();

}

void Assembler::program() {
    Node* node = this->root->children[0];
    if (node->id == declarationNode){
        declaration(node);
    }
    block(node);
}

void Assembler::declaration(Node* node) {
    varStack.push(node->token);
    if (node->children[0] != nullptr){
        declaration(node->children[0]);
    }
}

void Assembler::block(Node* node) {
    Node* child = this->root->children[0];
    if (node->id == declarationNode){
        declaration(node);
    }
    for (int i = 1; i < 4; i++ ){
        Node* child = this->root->children[i];
        if (child == nullptr) break;
        
    }

}
