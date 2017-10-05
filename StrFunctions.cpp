//
// Created by jamy on 10/1/17.
//

#include "StrFunctions.h"

void appendChar(char *destination, char source){
    int i = 0;
    while (destination[i] != '\0') {
        i++;
    }

    destination[i] = source;
    destination[i + 1] = '\0';
}

int equals(const char* word1, const char* word2){
    int i = 0;
    while (true){
        if (word1[i] != word2[i]) {return 1;}
        if (word1[i] == '\0' && word2[i] == '\0') { return 0; }
        i++;
    }
}
int equals(const char* word, char letter){

    if (word[0] != letter && word[1] == '\0') {return 1;}
    return 0;
}