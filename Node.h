//
// Created by jamy on 11/6/17.
//

#ifndef FRONTEND_NODE_H
#define FRONTEND_NODE_H

#include <vector>
#include "token.h"

enum nodeIdentifier{
    programNode,
    blockNode,
    declarationNode,
    identNode,
    statsNode,
    mStatNode,
    statNode,
    inNode,
    outNode,
    checkNode,
    loopNode,
    assignNode,
    exprNode,
    RNode,
    MNode,
    FNode,
    less,
    less_equals,
    greater,
    greater_equals,
    not_equals,
    equals_equals,
    plus,
    minus,
    percent,
    times,
    number
};

class Node {
private:
    nodeIdentifier id;
    struct token token;
    Node* children[4];

public:
    Node(nodeIdentifier id, struct token token);
    Node(nodeIdentifier id);
    ~Node();
    void insertChild(Node* node);

    bool hasChildren();
};


#endif //FRONTEND_NODE_H
