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

