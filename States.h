//
// Created by jamy on 9/29/17.
//
//Notes on Style--
//

#ifndef SCANNER_STATE_H
#define SCANNER_STATE_H

#include "Token.h"
#include "keywords.h"

#define ERROR -2
#define ENDOFFILE 0
#define WHITESPACE 1
#define LETTER 2
#define IDENTIFIER 2
#define DIGIT 3
#define EQUALS 4
#define EXCLAM 5
#define APPENDABLE_OPERATOR 6
#define FINAL_OPERATOR 7



class States {
public:
    bool isFinal;
    typedef States*(*FunctionPointer)(char*, Token*, States**);
    FunctionPointer driver[7];
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



#endif //SCANNER_STATE_H
