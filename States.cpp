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
* WhiteSpaceState functions
*
**************************************************************************************/

WhiteSpaceState::WhiteSpaceState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = ERR_tkn;
        appendChar(token->value, value);
        printf("ERROR: Invalid character: %c\n", value);
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = EOF_tkn;
        return (States*) nullptr;
    };
    driver[WHITESPACE] = [](char value, struct token* token, States** states) {
        if (value == '\n') { (token->line)++; }
        return states[WHITESPACE];
    };
    driver[LETTER] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        return states[LETTER];
    };
    driver[DIGIT] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        return states[DIGIT];
    };
    driver[EQUALS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        return states[EQUALS];
    };
    driver[EXCLAM] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        if(states[0] != nullptr) { delete (states[0]); }
        states[0] = new ExclamOperatorState();
        return states[0];
    };
    driver[GREATER_OPERATOR] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        if(states[0] != nullptr) { delete (states[0]); }
        states[0] = new GreaterOperatorState();
        return states[0];
    };
    driver[LESS_OPERATOR] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        if(states[0] != nullptr) { delete (states[0]); }
        states[0] = new LessOperatorState();
        return states[0];
    };
    driver[PLUS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = PLUS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[MINUS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = MINUS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[TIMES] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = TIMES_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[DIVIDE] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = DIVDE_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[AMPERSAND] = [](char value, struct token* token, States** states){
        appendChar(token->value, value);
        token->id = AMPERSAND_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[PERCENT] = [](char value, struct token* token, States** states){
        appendChar(token->value, value);
        token->id = PERCENT_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LEFT_BRACKET] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = LEFT_BRACKET_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[RIGHT_BRACKET] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = RIGHT_BRACKET_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LEFT_PAREN] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = LEFT_PAREN_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[RIGHT_PAREN] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = RIGHT_PAREN_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[LEFT_CURLY] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = LEFT_CURLY_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[RIGHT_CURLY] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = RIGHT_CURLY_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[DOT] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = DOT_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[COMMA] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = COMMA_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[SEMICOLON] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = SEMICOLON_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[COLON] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = COLON_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[HASH] = [](char value, struct token* token, States** states) {
        if(states[0] != nullptr) { delete (states[0]); }
        states[0] = new CommentState();
        return states[0];
    };
}

/**************************************************************************************
*
* NumberState functions
*
**************************************************************************************/
NumberState::NumberState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) nullptr;
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) nullptr;
    };
    driver[WHITESPACE] = driver[ENDOFFILE];
    driver[LETTER] = [](char value, struct token* token, States** states) {
        token->id = NUM_tkn;
        return (States*) nullptr;
    };
    driver[DIGIT] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);  
        return states[DIGIT];
    };
    driver[EQUALS] = driver[LETTER];
    driver[EXCLAM] = driver[LETTER];
    driver[GREATER_OPERATOR] = driver[LETTER];
    driver[LESS_OPERATOR] = driver[LETTER];
    driver[PLUS] = driver[LETTER];
    driver[MINUS] = driver[LETTER];
    driver[TIMES] = driver[LETTER];
    driver[DIVIDE] = driver[LETTER];
    driver[AMPERSAND] = driver[LETTER];
    driver[PERCENT] = driver[LETTER];
    driver[LEFT_BRACKET] = driver[LETTER];
    driver[RIGHT_BRACKET] = driver[LETTER];
    driver[LEFT_PAREN] = driver[LETTER];
    driver[RIGHT_PAREN] = driver[LETTER];
    driver[LEFT_CURLY] = driver[LETTER];
    driver[RIGHT_CURLY] = driver[LETTER];
    driver[DOT] = driver[LETTER];
    driver[COMMA] = driver[LETTER];
    driver[SEMICOLON] = driver[LETTER];
    driver[COLON] = driver[LETTER];
    driver[HASH] = driver[LETTER];
}

/**************************************************************************************
*
* IdentifierState functions
*
**************************************************************************************/
IdentifierState::IdentifierState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) nullptr;
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = IDENT_tkn;
        keywordCheck(token);
        return (States*) nullptr;
    };
    driver[WHITESPACE] = driver[ENDOFFILE];
    driver[LETTER] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        return states[LETTER];
    };
    driver[DIGIT] = driver[LETTER];
    driver[EQUALS] = driver[ENDOFFILE];
    driver[EXCLAM] = driver[ENDOFFILE];
    driver[GREATER_OPERATOR] = driver[ENDOFFILE];
    driver[LESS_OPERATOR] = driver[ENDOFFILE];
    driver[PLUS] = driver[ENDOFFILE];
    driver[MINUS] = driver[ENDOFFILE];
    driver[TIMES] = driver[ENDOFFILE];
    driver[DIVIDE] = driver[ENDOFFILE];
    driver[AMPERSAND] = driver[ENDOFFILE];
    driver[PERCENT] = driver[ENDOFFILE];
    driver[LEFT_BRACKET] = driver[ENDOFFILE];
    driver[RIGHT_BRACKET] = driver[ENDOFFILE];
    driver[LEFT_PAREN] = driver[ENDOFFILE];
    driver[RIGHT_PAREN] = driver[ENDOFFILE];
    driver[LEFT_CURLY] = driver[ENDOFFILE];
    driver[RIGHT_CURLY] = driver[ENDOFFILE];
    driver[DOT] = driver[ENDOFFILE];
    driver[COMMA] = driver[ENDOFFILE];
    driver[SEMICOLON] = driver[ENDOFFILE];
    driver[COLON] = driver[ENDOFFILE];
    driver[HASH] = driver[LETTER];
}

/**************************************************************************************
*
* GreaterOperatorState functions
*
**************************************************************************************/
GreaterOperatorState::GreaterOperatorState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = GREATER_tkn;
        return (States*) nullptr;
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = GREATER_tkn;
        return (States*) nullptr;
    };
    driver[WHITESPACE] = driver[ENDOFFILE];
    driver[LETTER] = [](char value, struct token* token, States** states) {
        token->id = GREATER_tkn;
        return (States*) nullptr;
    };
    driver[DIGIT] = driver[LETTER];
    driver[EQUALS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = GREATER_EQUALS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };    driver[EXCLAM] = driver[LETTER];
    driver[GREATER_OPERATOR] = driver[LETTER];
    driver[LESS_OPERATOR] = driver[LETTER];
    driver[PLUS] = driver[LETTER];
    driver[MINUS] = driver[LETTER];
    driver[TIMES] = driver[LETTER];
    driver[DIVIDE] = driver[LETTER];
    driver[AMPERSAND] = driver[LETTER];
    driver[PERCENT] = driver[LETTER];
    driver[LEFT_BRACKET] = driver[LETTER];
    driver[RIGHT_BRACKET] = driver[LETTER];
    driver[LEFT_PAREN] = driver[LETTER];
    driver[RIGHT_PAREN] = driver[LETTER];
    driver[LEFT_CURLY] = driver[LETTER];
    driver[RIGHT_CURLY] = driver[LETTER];
    driver[DOT] = driver[LETTER];
    driver[COMMA] = driver[LETTER];
    driver[SEMICOLON] = driver[LETTER];
    driver[COLON] = driver[LETTER];
    driver[HASH] = driver[LETTER];
}


EqualsOperatorState::EqualsOperatorState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = ERR_tkn;
        return (States*) nullptr;
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = EQUALS_tkn;
        return (States*) nullptr;
    };
    driver[WHITESPACE] = driver[ENDOFFILE];
    driver[LETTER] = [](char value, struct token* token, States** states) {
        token->id = EQUALS_tkn;
        return (States*) nullptr;
    };
    driver[DIGIT] = driver[LETTER];
    driver[EQUALS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = EQUALS_EQUALS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = driver[LETTER];
    driver[GREATER_OPERATOR] = driver[LETTER];
    driver[LESS_OPERATOR] = driver[LETTER];
    driver[PLUS] = driver[LETTER];
    driver[MINUS] = driver[LETTER];
    driver[TIMES] = driver[LETTER];
    driver[DIVIDE] = driver[LETTER];
    driver[AMPERSAND] = driver[LETTER];
    driver[PERCENT] = driver[LETTER];
    driver[LEFT_BRACKET] = driver[LETTER];
    driver[RIGHT_BRACKET] = driver[LETTER];
    driver[LEFT_PAREN] = driver[LETTER];
    driver[RIGHT_PAREN] = driver[LETTER];
    driver[LEFT_CURLY] = driver[LETTER];
    driver[RIGHT_CURLY] = driver[LETTER];
    driver[DOT] = driver[LETTER];
    driver[COMMA] = driver[LETTER];
    driver[SEMICOLON] = driver[LETTER];
    driver[COLON] = driver[LETTER];
    driver[HASH] = driver[LETTER];
}

ExclamOperatorState::ExclamOperatorState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = ERR_tkn;
        printf("ERROR: '!' must be followed by '='\n");
        return (States*) nullptr;
    };
    driver[ENDOFFILE] = driver[ERROR];
    driver[WHITESPACE] = driver[ERROR];
    driver[LETTER] = driver[ERROR];
    driver[DIGIT] = driver[ERROR];
    driver[EQUALS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = NOT_EQUALS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = driver[ERROR];
    driver[GREATER_OPERATOR] = driver[ERROR];
    driver[LESS_OPERATOR] = driver[ERROR];
    driver[PLUS] = driver[ERROR];
    driver[MINUS] = driver[ERROR];
    driver[TIMES] = driver[ERROR];
    driver[DIVIDE] = driver[ERROR];
    driver[AMPERSAND] = driver[ERROR];
    driver[PERCENT] = driver[ERROR];
    driver[LEFT_BRACKET] = driver[ERROR];
    driver[RIGHT_BRACKET] = driver[ERROR];
    driver[LEFT_PAREN] = driver[ERROR];
    driver[RIGHT_PAREN] = driver[ERROR];
    driver[LEFT_CURLY] = driver[ERROR];
    driver[RIGHT_CURLY] = driver[ERROR];
    driver[DOT] = driver[ERROR];
    driver[COMMA] = driver[ERROR];
    driver[SEMICOLON] = driver[ERROR];
    driver[COLON] = driver[ERROR];
    driver[HASH] = driver[ERROR];
}

LessOperatorState::LessOperatorState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        token->id = LESS_tkn;
        return (States*) nullptr;
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = LESS_tkn;
        return (States*) nullptr;
    };
    driver[WHITESPACE] = driver[ENDOFFILE];
    driver[LETTER] = [](char value, struct token* token, States** states) {
        token->id = LESS_tkn;
        return (States*) nullptr;
    };
    driver[DIGIT] = driver[LETTER];
    driver[EQUALS] = [](char value, struct token* token, States** states) {
        appendChar(token->value, value);
        token->id = LESS_EQUALS_tkn;
        states[WHITESPACE]->isFinal = true;
        return states[WHITESPACE];
    };
    driver[EXCLAM] = driver[LETTER];
    driver[GREATER_OPERATOR] = driver[LETTER];
    driver[LESS_OPERATOR] = driver[LETTER];
    driver[PLUS] = driver[LETTER];
    driver[MINUS] = driver[LETTER];
    driver[TIMES] = driver[LETTER];
    driver[DIVIDE] = driver[LETTER];
    driver[AMPERSAND] = driver[LETTER];
    driver[PERCENT] = driver[LETTER];
    driver[LEFT_BRACKET] = driver[LETTER];
    driver[RIGHT_BRACKET] = driver[LETTER];
    driver[LEFT_PAREN] = driver[LETTER];
    driver[RIGHT_PAREN] = driver[LETTER];
    driver[LEFT_CURLY] = driver[LETTER];
    driver[RIGHT_CURLY] = driver[LETTER];
    driver[DOT] = driver[LETTER];
    driver[COMMA] = driver[LETTER];
    driver[SEMICOLON] = driver[LETTER];
    driver[COLON] = driver[LETTER];
    driver[HASH] = driver[LETTER];
}

CommentState::CommentState() {
    isFinal = false;

    driver[ERROR] = [](char value, struct token* token, States** states) {
        return states[0];
    };
    driver[ENDOFFILE] = [](char value, struct token* token, States** states) {
        token->id = EOF_tkn;
        printf("WARNING: file ended within a comment\n");
        return (States *) nullptr;
    };
    driver[WHITESPACE] = [](char value, struct token* token, States** states) {
        if (value == '\n') { (token->line)++; }
        return states[0];
    };
    driver[LETTER] = driver[ERROR];
    driver[DIGIT] = driver[ERROR];
    driver[EQUALS] = driver[ERROR];
    driver[EXCLAM] = driver[ERROR];
    driver[GREATER_OPERATOR] = driver[ERROR];
    driver[LESS_OPERATOR] = driver[ERROR];
    driver[PLUS] = driver[ERROR];
    driver[MINUS] = driver[ERROR];
    driver[TIMES] = driver[ERROR];
    driver[DIVIDE] = driver[ERROR];
    driver[AMPERSAND] = driver[ERROR];
    driver[PERCENT] = driver[ERROR];
    driver[LEFT_BRACKET] = driver[ERROR];
    driver[RIGHT_BRACKET] = driver[ERROR];
    driver[LEFT_PAREN] = driver[ERROR];
    driver[RIGHT_PAREN] = driver[ERROR];
    driver[LEFT_CURLY] = driver[ERROR];
    driver[RIGHT_CURLY] = driver[ERROR];
    driver[DOT] = driver[ERROR];
    driver[COMMA] = driver[ERROR];
    driver[SEMICOLON] = driver[ERROR];
    driver[COLON] = driver[ERROR];
    driver[HASH] = [](char value, struct token* token, States** states) {
        return states[WHITESPACE];
    };
}
