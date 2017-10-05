//
// Created by jamy on 9/29/17.
//

#ifndef SCANNER_STATE_H
#define SCANNER_STATE_H

#include "Token.h"

#define ERROR -2
#define ENDOFFILE 0
#define WHITESPACE 1
#define LETTER 2
#define IDENTIFIER 2
#define DIGIT 3
#define APPENDABLE_OPERATOR 4
#define FINAL_OPERATOR 5
#define EQUALS 6


class States {
public:
    bool final;
    typedef States*(*FunctionPointer)(char*, Token*, States**);

    FunctionPointer driver[8];

};

class WhiteSpaceState: public States {
public:
    WhiteSpaceState();

};

class NumberState: public States {
public:
    NumberState();

protected:

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

class EndOfFileState: public States{
public:
    EndOfFileState();
};


#endif //SCANNER_STATE_H
