//
// Created by jamy on 9/30/17.
//
//
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include "States.h"
#include "StrFunctions.h"
#include "Token.h"

/**************************************************************************************
*
* WhiteSpaceState functions
*
**************************************************************************************/


WhiteSpaceState::WhiteSpaceState() {
    final = false;

    driver[ENDOFFILE] = [](char* value, Token* buffer, States** states) {
        buffer->id = EOF_tkn;
        strncpy(buffer->name, token_names[EOF_tkn], 12);
        strncpy(buffer->value, token_names[EOF_tkn], 12);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, Token* buffer, States** states) {
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[IDENTIFIER];
    };
    driver[DIGIT] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[EQUALS];
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[APPENDABLE_OPERATOR];
    };
    driver[FINAL_OPERATOR] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        appendChar(buffer->value, *value);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];
    };
}


/**************************************************************************************
*
* NumberState functions
*
**************************************************************************************/


NumberState::NumberState() {
    final = false;

    driver[ENDOFFILE] = [](char* value, Token* buffer, States** states) {
        buffer->id = NUM_tkn;
        strncpy(buffer->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, Token* buffer, States** states) {
        buffer->id = NUM_tkn;
        strncpy(buffer->name, token_names[NUM_tkn], 12);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, Token* buffer, States** states) {
        buffer->id = NUM_tkn;
        strncpy(buffer->name, token_names[NUM_tkn], 12);
        return (States*) NULL;

    };
    driver[DIGIT] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, Token* buffer, States** states) {
        buffer->id = NUM_tkn;
        strncpy(buffer->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
        ;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, Token* buffer, States** states) {
        buffer->id = NUM_tkn;
        strncpy(buffer->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, Token* buffer, States** states) {
        buffer->id = NUM_tkn;
        strncpy(buffer->name, token_names[NUM_tkn], 12);
        return (States*) NULL;

    };


}


/**************************************************************************************
*
* IdentifierState functions
*
**************************************************************************************/


IdentifierState::IdentifierState() {
    final = false;

    driver[ENDOFFILE] = [](char* value, Token* buffer, States** states) {
        buffer->id = IDENT_tkn;
        strncpy(buffer->name, token_names[IDENT_tkn], 12);
        return (States*) NULL;

    };
    driver[WHITESPACE] = [](char* value, Token* buffer, States** states) {
        buffer->id = IDENT_tkn;
        strncpy(buffer->name, token_names[IDENT_tkn], 12);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];

    };
    driver[LETTER] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[IDENTIFIER];
    };
    driver[DIGIT] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        return states[IDENTIFIER];
    };
    driver[EQUALS] = [](char* value, Token* buffer, States** states) {
        buffer->id = IDENT_tkn;
        strncpy(buffer->name, token_names[IDENT_tkn], 12);
        return (States*) NULL;

    };
    driver[APPENDABLE_OPERATOR] = [](char* value, Token* buffer, States** states) {
        buffer->id = IDENT_tkn;
        strncpy(buffer->name, token_names[IDENT_tkn], 12);
        return (States*) NULL;

    };
    driver[FINAL_OPERATOR] = [](char* value, Token* buffer, States** states) {
        buffer->id = IDENT_tkn;
        strncpy(buffer->name, token_names[IDENT_tkn], 12);
        return (States*) NULL;

    };
}



/**************************************************************************************
*
* OperatorState functions
*
**************************************************************************************/




AppendableOperatorState::AppendableOperatorState() {
    final = false;

    driver[ENDOFFILE] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;

    };
    driver[WHITESPACE] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];
    };
}


EqualsOperatorState::EqualsOperatorState() {
    final = false;

    driver[ENDOFFILE] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        return states[ENDOFFILE];
    };
    driver[WHITESPACE] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        states[IDENTIFIER]->final = true;
        return states[IDENTIFIER];
    };
    driver[DIGIT] = [](char* value, Token* buffer, States** states) {
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        states[DIGIT]->final = true;
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, Token* buffer, States** states) {
        appendChar(buffer->value, *value);
        buffer->id = OPERATOR_tkn;
        strncpy(buffer->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->final = true;
        return states[WHITESPACE];
    };

}

EndOfFileState::EndOfFileState() {
    this->final = true;

    driver[ENDOFFILE] = [](char* value, Token* buffer, States** states) {
        buffer->id = EOF_tkn;
        strncpy(buffer->name, token_names[EOF_tkn], 12);
        strncpy(buffer->value, token_names[EOF_tkn], 12);
        states[ENDOFFILE]->final = true;
        return states[ENDOFFILE];
    };

}
