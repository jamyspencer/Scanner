//
// Created by jamy on 9/30/17.
//
//
#include <stdexcept>
#include "States.h"
#include "StrFunctions.h"
#include "resolutions.h"
/**************************************************************************************
*
* Inheritable Constructor
*
**************************************************************************************/
States::States() {

}
/**************************************************************************************
*
* WhiteSpaceState functions
*
**************************************************************************************/

WhiteSpaceState::WhiteSpaceState() {
    isFinal = false;

    driver[ERROR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        appendChar(token->value, *value);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = EOF_tkn;
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
        appendChar(token->value, *value);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[PLUS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = PLUS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[MINUS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = MINUS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[TIMES] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = TIMES_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[DIVIDE] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = DIVDE_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LEFT_BRACKET] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = LEFT_BRACKET_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[RIGHT_BRACKET] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = RIGHT_BRACKET_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LEFT_PAREN] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = LEFT_PAREN_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[RIGHT_PAREN] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = RIGHT_PAREN_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LEFT_CURLY] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = LEFT_CURLY_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[RIGHT_CURLY] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = RIGHT_CURLY_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[DOT] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = DOT_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[COMMA] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = COMMA_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[SEMICOLON] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = SEMICOLON_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[COLON] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = COLON_tkn;
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

    driver[ERROR] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[PLUS] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[MINUS] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[TIMES] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[DIVIDE] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[LEFT_BRACKET] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[RIGHT_BRACKET] = driver[LETTER];
    driver[LEFT_PAREN] = driver[LETTER];
    driver[RIGHT_PAREN] = driver[LETTER];
    driver[LEFT_CURLY] = driver[LETTER];
    driver[RIGHT_CURLY] = driver[LETTER];
    driver[DOT] = driver[LETTER];
    driver[COMMA] = [](char* value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) NULL;
    };
    driver[SEMICOLON] = driver[LETTER];
    driver[COLON] = driver[LETTER];
}

/**************************************************************************************
*
* IdentifierState functions
*
**************************************************************************************/
IdentifierState::IdentifierState() {
    isFinal = false;

    driver[ERROR] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
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
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) NULL;
    };
    driver[PLUS] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        return (States*) NULL;
    };
    driver[MINUS] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        return (States*) NULL;
    };
    driver[TIMES] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        return (States*) NULL;
    };
    driver[DIVIDE] = [](char* value, struct token* token, States** states) {
        token->id = IDENT_tkn;
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

    driver[ERROR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = OPERATOR_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[PLUS] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[MINUS] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[TIMES] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[DIVIDE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
}


EqualsOperatorState::EqualsOperatorState() {
    isFinal = false;

    driver[ERROR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return states[ENDOFFILE];
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = EQUALS_EQUALS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[PLUS] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[MINUS] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[TIMES] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
    driver[DIVIDE] = [](char* value, struct token* token, States** states) {
        token->id = OPERATOR_tkn;
        return (States*) NULL;
    };
}

ExclamOperatorState::ExclamOperatorState() {
    isFinal = false;

    driver[ERROR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[ENDOFFILE] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[WHITESPACE] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[DIGIT] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[EQUALS] = [](char* value, struct token* token, States** states) {
        appendChar(token->value, *value);
        token->id = NOT_EQUALS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[APPENDABLE_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[FINAL_OPERATOR] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[PLUS] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[MINUS] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[TIMES] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
    driver[DIVIDE] = [](char* value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) NULL;
    };
}


