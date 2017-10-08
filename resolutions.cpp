//
// Created by jamy on 10/7/17.
//

#include "resolutions.h"
#include <cstring>

std::unordered_map<char*, bool> keywords = {
        {"Begin", true}, {"End", true}, {"Check", true}, {"Loop", true}, {"Void", true},
        {"Var", true}, {"Return", true}, {"Input", true}, {"Output", true}, {"Program", true} };
//static const char keywords[KEYWORD_COUNT][8] = { "Begin", "End", "Check", "Loop", "Void", "Var", "Return", "Input", "Output", "Program" };

void keywordCheck(token* token){
    if (keywords[token->value]){
        token->id = KEYWORD_tkn;
        strncpy(token->name, token_names[KEYWORD_tkn], 12);
    }
}