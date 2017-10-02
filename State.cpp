//
// Created by jamy on 9/30/17.
//
#include <typeinfo>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "State.h"
#include "StrFunctions.h"

void State::tokenize(char* buffer) const{
    printf("%s\n", buffer);
    buffer[0] = '\0';
}


State* State::handleNumber(char value, char* buffer, States* states) const {
    appendChar(buffer, value);
    return states->number;
}

State* State::handleLetter(char value, char* buffer, States* states) const {
    appendChar(buffer, value);
    return states->identifier;
}

State* State::handleUnderscore(char value, char* buffer, States* states) const {
    printf("ERROR: underscores cannot begin a token");
    return NULL;
}

State* State::handleOperatorChar(char value, char* buffer, States* states) const {
    appendChar(buffer, value);
    return states->operatr;
}

State* State::handleWhiteSpace(char* buffer, States* states) const {
    tokenize(buffer);
    return states->white;
}

State* State::handleEOF(char* buffer, States* states) const {
    tokenize(buffer);
    printf("Scanning Complete\n");
    return NULL;
}

State* State::evaluate(char value, char* buffer, States* states) {

    if (value == '\377'){//check for eof
        return handleEOF(buffer, states);
    }

    else if (value == 10 || value == 32){//check for space or newlines
        return handleWhiteSpace(buffer, states);
    }

    else if (value >= 48 && value<=57){//check for numbers
        return handleNumber(value, buffer, states);
    }

    else if ((value >= 65 && value <= 90) || (value >= 97 && value <= 122)){//check for letters
        return handleLetter(value, buffer, states);
    }

    else if (value == '_'){
        return handleUnderscore(value, buffer, states);
    }

    else if (value == '<', '>', '='){
        return handleOperatorChar(value, buffer, states);
    }
    return NULL;
}

/**************************************************************************************
*
* WhiteSpaceState functions
*
**************************************************************************************/
State* WhiteSpaceState::handleEOF(char* buffer, States* states) const {
    printf("Scanning Complete\n");
    return NULL;
}

State* WhiteSpaceState::handleWhiteSpace(char* buffer, States* states) const {
    return states->white;
}

State* WhiteSpaceState::handleOperatorChar(char value, char* buffer, States* states) const {
    appendChar(buffer, value);
    return states->operatr;
}


/**************************************************************************************
*
* NumberState functions
*
**************************************************************************************/


State* NumberState::handleLetter(char value, char* buffer, States* states) const {
    printf("ERROR: Numbers cannot contain letters.\n");
    return NULL;
}

State* NumberState::handleOperatorChar(char value, char* buffer, States* states) const {
    tokenize(buffer);
    appendChar(buffer, value);
    return states->operatr;
}


/**************************************************************************************
*
* IdentifierState functions
*
**************************************************************************************/

State* IdentifierState::handleUnderscore(char value, char* buffer, States* states) const {
    appendChar(buffer, value);
    return states->identifier;
}

State* IdentifierState::handleOperatorChar(char value, char* buffer, States* states) const {
    tokenize(buffer);
    appendChar(buffer, value);
    return states->operatr;
}

/**************************************************************************************
*
* OperatorState functions
*
**************************************************************************************/

State* OperatorState::handleLetter(char value, char* buffer, States* states) const {
    tokenize(buffer);
    appendChar(buffer, value);
    return states->identifier;
}

State* OperatorState::handleNumber(char value, char* buffer, States* states) const {
    tokenize(buffer);
    appendChar(buffer, value);
    return states->number;
}

void OperatorState::tokenize(char* buffer) const {
    char gtequals[] = ">=";
    char ltequals[] = "<=";

    if (equals(buffer, '<') || equals(buffer, '>') || equals(buffer, '=') || equals(buffer, gtequals) || equals(buffer,ltequals)) {
        State::tokenize(buffer);
    }else{
        throw std::runtime_error( "Bad Operator Token" );
    }

}




