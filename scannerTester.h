//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_SCANNERTESTER_H
#define FRONTEND_SCANNERTESTER_H

#include "Scanner.h"
#include "token.h"

class Parser{
public:
    Parser(FILE*);
    void parse();

private:
    Scanner scanner;
    struct token currentToken;
};

#endif
