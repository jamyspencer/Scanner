//
// Created by jamy on 10/1/17.
//

#ifndef SCANNER_MAIN_H
#define SCANNER_MAIN_H

#include "States.h"

#define BUFSIZE 64



class ScannerObject{
public:
    ScannerObject(FILE *file);
    struct Token getToken();
};
#endif //SCANNER_MAIN_H
