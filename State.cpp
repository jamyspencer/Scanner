//
// Created by jamy on 9/30/17.
//
#include <cstring>
#include <cstdio>
#include "State.h"
#include "MyStringFunctions.h"

void State::tokenize(char* buffer) const{
    printf("%s\n", buffer);
    buffer[0] = '\0';
}

State* State::handleEOF(char* buffer, States* states) const{
    tokenize(buffer);
    printf("Scanning Complete\n");
    return NULL;
}

State *State::handleNumber(char value, char *buffer, States *states) const {
    appendChar(buffer, value);
    return states->number;
}

State * State::evaluate(char value, char *buffer, States *states) {

    if (value == 10 || value == 32){//check for space or newlines
        return handleWhiteSpace(buffer, states);
    }

    if (value >= 48 && value<=57){//check for numbers
        return handleNumber(value, buffer, states);
    }

    if ((value >= 65 && value <= 90) || (value >= 97 && value <= 122)){//check for letters
        return handleLetter(value, buffer, states);
    }

    if (value == '_'){
        return handleUnderscore(value, buffer, states);
    }

    if (value == '\377'){//check for eof
        return handleEOF(buffer, states);
    }

    return NULL;
}

State * WhiteSpaceState::handleWhiteSpace(char *buffer, States *states) const {
    return states->white;
}

State * WhiteSpaceState::handleLetter(char value, char *buffer, States *states) const {
    appendChar(buffer, value);
    return states->identifier;
}

State * WhiteSpaceState::handleUnderscore(char value, char *buffer, States *states) const {
    printf("ERROR: underscores cannot begin a token");
    return NULL;
}


State * NumberState::handleWhiteSpace(char *buffer, States *states) const {
    tokenize(buffer);
    return states->white;
}

State * NumberState::handleLetter(char value, char *buffer, States *states) const {
    printf("ERROR: Numbers cannot contain letters.\n");
    return NULL;
}

State * NumberState::handleUnderscore(char value, char *buffer, States *states) const {
    printf("ERROR: Numbers cannot contain underscores.\n");
    return NULL;
}

State * IdentifierState::handleWhiteSpace(char *buffer, States *states) const {
    tokenize(buffer);
    return states->white;
}

State * IdentifierState::handleLetter(char value, char *buffer, States *states) const {
    appendChar(buffer, value);
    return states->identifier;
}

State * IdentifierState::handleUnderscore(char value, char *buffer, States *states) const {
    appendChar(buffer, value);
    return states->identifier;
}
