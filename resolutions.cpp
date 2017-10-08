//
// Created by jamy on 10/7/17.
//

#include "resolutions.h"
#include <cstring>

std::unordered_map<std::string, bool> keywords = {
        {"Begin", true}, {"End", true}, {"Check", true}, {"Loop", true}, {"Void", true},
        {"Var", true}, {"Return", true}, {"Input", true}, {"Output", true}, {"Program", true} };

void keywordCheck(token* token){
    std::string check = std::string(token->value);
    if (keywords[check]){
        token->id = KEYWORD_tkn;
        strncpy(token->name, token_names[KEYWORD_tkn], 12);
    }
}