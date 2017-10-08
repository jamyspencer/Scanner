//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_SCANNER_H
#define FRONTEND_SCANNER_H

#include <unordered_map>
#include "States.h"

#define BUFSIZE 64

class Scanner{
private:
    States *states[7];
    States *currentState;
    FILE* file;
    char value;
    struct token token;
    std::unordered_map<char, int> map;

public:
    Scanner(FILE *file);
    struct token getToken();
    ~Scanner();
};
#endif
