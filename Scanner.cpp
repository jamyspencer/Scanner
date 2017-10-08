//
// Created by jamy on 10/7/17.
//

#include <stdio.h>
#include <cstdlib>

#include "Scanner.h"
#include "token.h"

struct token Scanner::getToken() {

    token.value[0] = '\0';

    //this corrects the state due to look-aheads
    if (currentState == NULL) {
        currentState = states[WHITESPACE];
        currentState = currentState->driver[map[value]](&value, &token, states);
    } else {
        currentState->isFinal = false;
    }
    //primary token generating loop
    while (currentState != NULL && !currentState->isFinal) {
        value = fgetc(file);
        currentState = currentState->driver[map[value]](&value, &token, states);
    }

    return token;
}

Scanner::Scanner(FILE* file): file(file), map(std::unordered_map<char, int> (
        {{'\t', WHITESPACE}, {'\n', WHITESPACE}, {' ', WHITESPACE}, {-1, ENDOFFILE},
         {'<', APPENDABLE_OPERATOR}, {'>', APPENDABLE_OPERATOR},
         {'[', FINAL_OPERATOR}, {']', FINAL_OPERATOR}, {'(', FINAL_OPERATOR},
         {')', FINAL_OPERATOR}, {'{', FINAL_OPERATOR}, {'}', FINAL_OPERATOR}, {'=', EQUALS},
         {'!', EXCLAM}
        })) {
    int i;
    for (i = 48; i < 58; i++) { map.emplace(i, DIGIT); }
    for (i = 65; i < 91; i++){ map.emplace (i, LETTER); } //upper
    for (i = 97 ; i < 123; i++){  map.emplace(i, LETTER); } //lower


    states[WHITESPACE] = (States *) new WhiteSpaceState();
    states[LETTER] = (States *) new IdentifierState();
    states[DIGIT] = (States *) new NumberState();
    states[EQUALS] = (States *) new EqualsOperatorState();
    states[EXCLAM] = (States *) new ExclamOperatorState();
    states[APPENDABLE_OPERATOR] = (States *) new AppendableOperatorState();
    currentState = states[WHITESPACE];
}

Scanner::~Scanner() {
    delete(states[WHITESPACE]);
    delete(states[LETTER]);
    delete(states[DIGIT]);
    delete(states[EQUALS]);
    delete(states[EXCLAM]);
    delete(states[APPENDABLE_OPERATOR]);
}
