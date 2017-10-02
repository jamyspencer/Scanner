//
// Created by jamy on 9/29/17.
//

#ifndef SCANNER_STATE_H
#define SCANNER_STATE_H


#include "States.h"

#define ERROR -1
#define WHITE 0
#define NUMBER 1
#define IDENTIFIER 2

class States;

class State {

public:
    State * evaluate(char value, char *buffer, States *states);

protected:
    void tokenize(char* buffer) const;
    State* handleEOF(char* buffer, States* states) const;
    virtual State *handleWhiteSpace(char *buffer, States *states) const = 0;
    virtual State * handleNumber(char value, char *buffer, States *states) const;
    virtual State * handleLetter(char value, char *buffer, States *states) const = 0;
    virtual State * handleUnderscore(char value, char *buffer, States *states) const = 0;
};

class WhiteSpaceState: public State {
    State *handleWhiteSpace(char *buffer, States *states) const override;
    State * handleLetter(char value, char *buffer, States *states) const override;
    State * handleUnderscore(char value, char *buffer, States *states) const override;

};

class NumberState: public State {
    State * handleWhiteSpace(char *buffer, States *states) const override;
    State * handleLetter(char value, char *buffer, States *states) const override;
    State * handleUnderscore(char value, char *buffer, States *states) const override;

};

class IdentifierState: public State{
    State * handleWhiteSpace(char *buffer, States *states) const override;
    State * handleLetter(char value, char *buffer, States *states) const override;
    State * handleUnderscore(char value, char *buffer, States *states) const override;
};

#include "States.h"

#endif //SCANNER_STATE_H
