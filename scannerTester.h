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
    int array_size = 100;
    int array_elements = 0;
    token* token_array = (token*) malloc (sizeof(token) * array_size);
    FILE* source_file;
    Scanner scanner;

};

#endif
