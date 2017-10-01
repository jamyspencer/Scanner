//
// Created by jamy on 9/30/17.
//
#include <cstring>
#include <cstdio>
#include "State.h"

void State::tokenize(char* buffer) const{
    printf("%s\n", buffer);
    buffer[0] = '\0';
}

State * State::evaluate(char value, char *buffer, States *states) {
    const char WHITESPACE[] = {' ', '\n'};

    for (char ws: WHITESPACE){
        if (value == ws) return handleWhiteSpace(buffer, states);
    }

    return NULL;
}

State * WhiteSpaceState::handleWhiteSpace(char *buffer, States *states) const {
    return states->white;
}

State * WhiteSpaceState::handleNumber(char value, char *buffer, States *states) const {
    strcat(buffer, &value);
    return states->number;
}

State * WhiteSpaceState::handleLetter(char value, char *buffer, States *states) const {
    strcat(buffer, &value);
    return states->identifier;
}

State * WhiteSpaceState::handleUnderscore(char value, char *buffer, States *states) const {
    return NULL;
}


State * NumberState::handleWhiteSpace(char *buffer, States *states) const {
    tokenize(buffer);
    return states->white;
}

State * NumberState::handleNumber(char value, char *buffer, States *states) const {
    strcat(buffer, &value);
    return states->number;
}

State * NumberState::handleLetter(char value, char *buffer, States *states) const {
    return NULL;
}

State * NumberState::handleUnderscore(char value, char *buffer, States *states) const {
    return NULL;
}

State * IdentifierState::handleWhiteSpace(char *buffer, States *states) const {
    return states->white;
}

State * IdentifierState::handleNumber(char value, char *buffer, States *states) const {
    strcat(buffer, &value);
    return states->identifier;
}

State * IdentifierState::handleLetter(char value, char *buffer, States *states) const {
    strcat(buffer, &value);
    return states->identifier;
}

State * IdentifierState::handleUnderscore(char value, char *buffer, States *states) const {
    strcat(buffer, &value);
    return states->identifier;
}
