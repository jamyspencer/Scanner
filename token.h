//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_TOKEN_H
#define FRONTEND_TOKEN_H


extern char* token_names[22];

enum token_id{
    ERR_tkn,
    PLUS_tkn,
    MINUS_tkn,
    TIMES_tkn,
    DIVDE_tkn,
    LEFT_BRACKET_tkn,
    RIGHT_BRACKET_tkn,
    LEFT_PAREN_tkn,
    RIGHT_PAREN_tkn,
    LEFT_CURLY_tkn,
    RIGHT_CURLY_tkn,
    DOT_tkn,
    COMMA_tkn,
    SEMICOLON_tkn,
    COLON_tkn,
    NOT_EQUALS_tkn,
    EQUALS_EQUALS_tkn,
    NUM_tkn,
    IDENT_tkn,
    KEYWORD_tkn,
    OPERATOR_tkn,
    EOF_tkn
};

struct token {
    token_id id;
    char value[10];
    int row;
};
#endif
