//
// Created by jamy on 10/7/17.
//

#include "token.h"

char err[] = "ERROR";
char eof[] = "EOF";
char ident[] = "Identifier";
char keyword[] = "Keyword";
char num[] = "Number";
char op[] = "Operator";

char* token_names[8] = {err, eof, ident, keyword, num, op};