//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_TOKEN_H
#define FRONTEND_TOKEN_H


extern const char* token_names[28];

enum token_id{
    ERR_tkn,
    PLUS_tkn,
    MINUS_tkn,
    TIMES_tkn,
    DIVDE_tkn,
    AMPERSAND_tkn,
    PERCENT_tkn,
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
    EQUALS_tkn,
    GREATER_tkn,
    LESS_tkn,
    GREATER_EQUALS_tkn,
    LESS_EQUALS_tkn,
    EOF_tkn,

    BEGIN_KEYWORD_tkn,
    END_KEYWORD_tkn,
    CHECK_KEYWORD_tkn,
    LOOP_KEYWORD_tkn,
    VOID_KEYWORD_tkn,
    VAR_KEYWORD_tkn,
    RETURN_KEYWORD_tkn,
    INPUT_KEYWORD_tkn,
    OUTPUT_KEYWORD_tkn,
    PROGRAM_KEYWORD_tkn
};

struct token {
    token_id id;
    char value[10];
    int line;
};
#endif
