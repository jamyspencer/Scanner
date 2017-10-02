//
// Created by jamy on 10/1/17.
//

#include "MyStringFunctions.h"

void appendChar(char *destination, char source){
    int i = 0, j = 0;
    while (destination[i] != '\0') {
        i++;
    }

    destination[i] = source;
    destination[i + 1] = '\0';
}