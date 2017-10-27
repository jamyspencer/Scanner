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
#define APPENDABLE_OPERATOR 6
#define FINAL_OPERATOR 7
#define ENDOFFILE 8
#define PLUS 9
#define MINUS 10
#define TIMES 11
#define DIVIDE 12
#define LEFT_BRACKET 13
#define RIGHT_BRACKET 14
#define LEFT_PAREN 15
#define RIGHT_PAREN 16
#define LEFT_CURLY 17
#define RIGHT_CURLY 18
#define DOT 19
#define COMMA 20
#define SEMICOLON 21
#define COLON 22

class States {
public:
    bool isFinal;
    typedef States*(*FunctionPointer)(char*, token*, States**);
    FunctionPointer driver[23];

    States();
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

class AppendableOperatorState: public States{
public:
    AppendableOperatorState();
};

class EqualsOperatorState: public States{
public:
    EqualsOperatorState();
};

class ExclamOperatorState: public States{
public:
    ExclamOperatorState();
};

#endif
