//
// Created by jamy on 10/7/17.
//

#include "resolutions.h"
#include <cstring>

std::unordered_map<std::string, token_id > keywords = {
        {"Begin", BEGIN_KEYWORD_tkn}, {"End", END_KEYWORD_tkn}, {"Check", CHECK_KEYWORD_tkn},
        {"Loop", LOOP_KEYWORD_tkn}, {"Void", VOID_KEYWORD_tkn}, {"Var", VAR_KEYWORD_tkn},
        {"Return", RETURN_KEYWORD_tkn}, {"Input", INPUT_KEYWORD_tkn}, {"Output", OUTPUT_KEYWORD_tkn},
        {"Program", PROGRAM_KEYWORD_tkn} };

void keywordCheck(token* token){
    std::string check = std::string(token->value);
    if (keywords[check]){

        token->id = keywords[check];
    }
}