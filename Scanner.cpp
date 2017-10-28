//
// Created by jamy on 10/7/17.
//

#include <stdio.h>
#include <cstdlib>

#include "Scanner.h"

struct token Scanner::getToken() {

    token.value[0] = '\0';

    //this corrects the state due to look-aheads
    if (currentState == nullptr) {
        currentState = states[WHITESPACE];
        currentState = currentState->driver[map[value]](value, &token, states);
    } else {
        currentState->isFinal = false;
    }
    //primary token generating loop
    while (currentState != nullptr && !currentState->isFinal) {
        value = fgetc(file);
        currentState = currentState->driver[map[value]](value, &token, states);
    }

    return token;
}

Scanner::Scanner(FILE* file): file(file), map(std::unordered_map<char, int> (
        {{'\t', WHITESPACE}, {'\n', WHITESPACE}, {' ', WHITESPACE}, {-1, ENDOFFILE},
         {'<', LESS_OPERATOR}, {'>', GREATER_OPERATOR}, {'%', PERCENT},
         {'+', PLUS}, {'-', MINUS}, {'*', TIMES}, {'/', DIVIDE}, {'&', AMPERSAND},
         {'[', LEFT_BRACKET}, {']', RIGHT_BRACKET}, {'(', LEFT_PAREN},
         {')', RIGHT_PAREN}, {'{', LEFT_CURLY}, {'}', RIGHT_CURLY}, {'.', DOT},
         {',', COMMA}, {';', SEMICOLON}, {':', COLON}, {'=', EQUALS}, {'!', EXCLAM},
         {'#', HASH}
        })) {
    int i;
    for (i = 48; i < 58; i++) { map.emplace(i, DIGIT); }
    for (i = 65; i < 91; i++){ map.emplace (i, LETTER); } //upper
    for (i = 97 ; i < 123; i++){  map.emplace(i, LETTER); } //lower

    token.line = 1;

    states[0] = nullptr;
    states[WHITESPACE] = (States *) new WhiteSpaceState();
    states[LETTER] = (States *) new IdentifierState();
    states[DIGIT] = (States *) new NumberState();
    states[EQUALS] = (States *) new EqualsOperatorState();

    currentState = states[WHITESPACE];

//    printf("mymap contains:\n");
//    for ( auto it = map.begin(); it != map.end(); ++it )
//        printf(" %c:%d\n", it->first, it->second);
}

Scanner::~Scanner() {
    delete(states[0]);
    delete(states[WHITESPACE]);
    delete(states[LETTER]);
    delete(states[DIGIT]);
    delete(states[EQUALS]);
}
