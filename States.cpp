//
// Created by jamy on 9/30/17.
//
//
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include "States.h"
#include "StrFunctions.h"
#include "resolutions.h"

/**************************************************************************************
*
* WhiteSpaceState functions
*
**************************************************************************************/

WhiteSpaceState::WhiteSpaceState() {
    isFinal = false;

    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = EOF_tkn;
        strncpy(token->name, token_names[EOF_tkn], 12);
        strncpy(token->value, token_names[EOF_tkn], 12);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[LETTER];
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[EQUALS];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[EXCLAM];
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[APPENDABLE_OPERATOR];
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        appendChar(token->value, *value);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
}

/**************************************************************************************
*
* NumberState functions
*
**************************************************************************************/
NumberState::NumberState() {
    isFinal = false;

    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        return (States*) NULL;

    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        strncpy(token->name, token_names[NUM_tkn], 12);
        return (States*) NULL;

    };
}

/**************************************************************************************
*
* IdentifierState functions
*
**************************************************************************************/
IdentifierState::IdentifierState() {
    isFinal = false;

    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        strncpy(token->name, token_names[IDENT_tkn], 12);
        keywordCheck(token);
        return (States*) NULL;

    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        strncpy(token->name, token_names[IDENT_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        keywordCheck(token);
        return states[WHITESPACE];

    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[LETTER];
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[LETTER];
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        strncpy(token->name, token_names[IDENT_tkn], 12);
        keywordCheck(token);
        return (States*) NULL;

    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        strncpy(token->name, token_names[IDENT_tkn], 12);
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        strncpy(token->name, token_names[IDENT_tkn], 12);
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        strncpy(token->name, token_names[IDENT_tkn], 12);
        keywordCheck(token);
        return (States*) NULL;

    };
}

/**************************************************************************************
*
* OperatorState functions
*
**************************************************************************************/
AppendableOperatorState::AppendableOperatorState() {
    isFinal = false;

    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;

    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;

    };
}


EqualsOperatorState::EqualsOperatorState() {
    isFinal = false;

    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return states[ENDOFFILE];
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;

    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        return (States*) NULL;

    };
}

ExclamOperatorState::ExclamOperatorState() {
    isFinal = false;

    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        return (States*) NULL;
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = OPERATOR_tkn;
        strncpy(token->name, token_names[OPERATOR_tkn], 12);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        return (States*) NULL;

    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        strncpy(token->name, token_names[ERR_tkn], 12);
        return (States*) NULL;

    };
}