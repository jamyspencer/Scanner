//
// Created by jamy on 11/6/17.
//

#include <cstdlib>
#include <cstdio>
#include <string>
#include "Node.h"

static const char* nodeNames[] = {
        "program",
        "block",
        "declaration",
        "ident",
        "stats",
        "mStat",
        "stat",
        "in",
        "outFile",
        "check",
        "loop",
        "assign",
        "expr",
        "R",
        "M",
        "F",
        "less",
        "less_equals",
        "greater",
        "greater_equals",
        "not_equals",
        "equals_equals"
};

Node::Node(nodeIdentifier id, struct token token) : id(id), token(token) {
    for (int i = 0; i < 4; i++){
        children[i] = nullptr;
    }
}
Node::Node(nodeIdentifier id) : id(id) {
    for (int i = 0; i < 4; i++){
        children[i] = nullptr;
    }
}

Node::~Node() {
    for (int i = 0; i < 4; i++){
        delete children[i];
    }
}

void Node::insertChild(Node* node) {
    for (int i = 0; i < 4; i++){
        if (children[i] == nullptr){
            children[i] = node;
            if (node != nullptr) node->parent = this;
            break;
        }
    }
}

void Node::reduceTree(int siblingIndex){

    if (children[0] == nullptr) return;
    for (int i = 0; i < 4; i++){
        if (children[i] != nullptr){
            children[i]->reduceTree(i);
        }
    }
    switch (id) {
        case MNode:
        case RNode:
        case exprNode:
            if (this->token.id == BLANK_tkn && this->children[1] == nullptr) {
                parent->children[siblingIndex] = children[0];
                children[0] = nullptr;
                delete this;
            }
            break;
    }
}

void Node::traversePreOrder(){
    static int level = 0;
    printf("%*c%d:%-9s ", level * 2,' ', level, nodeNames[this->id]); // assume some info printed as string
    if (this->token.id != BLANK_tkn )printf("%s: %s", token_names[this->token.id], (this->token.value));
    printf("\n");
    level++;
    for (int i = 0; i < 4; i++){
        if (this->children[i] != nullptr){
            this->children[i]->traversePreOrder();
            level--;
        }
    }
}

bool Node::hasChildren() {
    return this->children[0] != nullptr;
}

