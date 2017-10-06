//
// Created by jamy on 10/4/17.
//

#ifndef SCANNER_TOKEN_H
#define SCANNER_TOKEN_H


extern char* token_names[8];

enum token_id{
    ERR_tkn,
    EOF_tkn,
    IDENT_tkn,
    NUM_tkn,
    OPERATOR_tkn
};

struct Token {
    char name[12];
    token_id id;
    char value[10];
};


#endif //SCANNER_TOKEN_H
