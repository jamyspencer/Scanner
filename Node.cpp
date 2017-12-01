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
        "out",
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
        "equals_equals",
        "plus",
        "minus",
        "percent",
        "times",
        "number"
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
            break;
        }
    }
}

bool Node::hasChildren() {
    return this->children[0] != nullptr;
}

