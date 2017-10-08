//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_STATES_H
#define FRONTEND_STATES_H

#include "token.h"

#define WHITESPACE 0
#define LETTER 1
#define DIGIT 2
#define EQUALS 3
#define EXCLAM 4
#define APPENDABLE_OPERATOR 5
#define FINAL_OPERATOR 6
#define ERROR 7
#define ENDOFFILE 8


class States {
public:
    bool isFinal;
    typedef States*(*FunctionPointer)(char*, token*, States**);
    FunctionPointer driver[9];
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
