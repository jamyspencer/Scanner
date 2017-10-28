//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_STATES_H
#define FRONTEND_STATES_H

#include "token.h"

#define ERROR 0
#define WHITESPACE 1
#define LETTER 2
#define DIGIT 3
#define EQUALS 4
#define EXCLAM 5
#define GREATER_OPERATOR 6
#define LESS_OPERATOR 7
#define ENDOFFILE 8
#define PLUS 9
#define MINUS 10
#define TIMES 11
#define DIVIDE 12
#define AMPERSAND 13
#define PERCENT 14
#define LEFT_BRACKET 15
#define RIGHT_BRACKET 16
#define LEFT_PAREN 17
#define RIGHT_PAREN 18
#define LEFT_CURLY 19
#define RIGHT_CURLY 20
#define DOT 21
#define COMMA 22
#define SEMICOLON 23
#define COLON 24
#define HASH 25

class States {
public:
    bool isFinal;
    typedef States*(*FunctionPointer)(char, token*, States**);
    FunctionPointer driver[26];
};

class WhiteSpaceState: public States {
public:
    WhiteSpaceState();
};

class NumberState: public States {
public:
    NumberState();
};

class IdentifierState: public States{
public:
    IdentifierState();
};

class GreaterOperatorState: public States{
public:
    GreaterOperatorState();
};

class LessOperatorState: public States{
public:
    LessOperatorState();
};

class EqualsOperatorState: public States{
public:
    EqualsOperatorState();
};

class ExclamOperatorState: public States{
public:
    ExclamOperatorState();
};

class CommentState: public States{
public:
    CommentState();
};

#endif
