//
// Created by jamy on 9/29/17.
//

#ifndef SCANNER_STATE_H
#define SCANNER_STATE_H


#include "States.h"

class States;

class State {
protected:
    char tokenCode[12] = {'\0'};

public:
    State* evaluate(char value, char* buffer, States* states);

protected:
    virtual void tokenize(char* buffer) const;
    virtual State* handleEOF(char* buffer, States* states) const;
    virtual State* handleWhiteSpace(char* buffer, States* states) const;
    virtual State* handleNumber(char value, char* buffer, States* states) const;
    virtual State* handleLetter(char value, char* buffer, States* states) const;
    virtual State* handleUnderscore(char value, char* buffer, States* states) const;
    virtual State* handleOperatorChar(char value, char* buffer, States* states) const;
};

class WhiteSpaceState: public State {

private:
    State* handleWhiteSpace(char* buffer, States* states) const override;
    State* handleOperatorChar(char value, char* buffer, States* states) const override;
    State* handleEOF(char* buffer, States* states) const override;

};

class NumberState: public State {
private:
    State* handleLetter(char value, char* buffer, States* states) const override;
    State* handleOperatorChar(char value, char* buffer, States* states) const override;
};

class IdentifierState: public State{
private:
    State* handleUnderscore(char value, char* buffer, States* states) const override;
    State* handleOperatorChar(char value, char* buffer, States* states) const override;
};

class OperatorState: public State{
    
private:
    State* handleNumber(char value, char* buffer, States* states) const override;
    State* handleLetter(char value, char* buffer, States* states) const override;
    void tokenize(char* buffer) const override;
};

#include "States.h"

#endif //SCANNER_STATE_H
