//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_TOKEN_H
#define FRONTEND_TOKEN_H


extern char* token_names[8];

enum token_id{
    ERR_tkn,
    EOF_tkn,
    IDENT_tkn,
    KEYWORD_tkn,
    NUM_tkn,
    OPERATOR_tkn
};

struct token {
    char name[13];
    token_id id;
    char value[10];
};
#endif
