#include <cstdio>
#include <cstdlib>


#include "scanner.h"
#include "Token.h"

    static States *states[7];
    static States *currentState;
    static FILE *info_file;
    char value;

    static std::unordered_map<char, int> map;


ScannerObject:: Token getToken() {
    struct Token token;
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
        value = fgetc(info_file);
        currentState = currentState->driver[map[value + 1]](&value, &token, states);
    }

    return token;
}

ScannerObject::ScannerObject(FILE *file) {
    int i;
    map = {{'\t', WHITESPACE}, {'\n', WHITESPACE}, {' ', WHITESPACE}, {-1, EOF},
           {'<', APPENDABLE_OPERATOR}, {'>', APPENDABLE_OPERATOR}, 
           {'[', FINAL_OPERATOR}, {']', FINAL_OPERATOR}, {'(', FINAL_OPERATOR},
           {')', FINAL_OPERATOR}, {'{', FINAL_OPERATOR}, {'}', FINAL_OPERATOR}, {'=', EQUALS},
           {'!', EXCLAM},
    };
    for (i = 48; i < 58; i++) { map.emplace(i, DIGIT); }
    for (i = 65; i < 91; i++){ map.emplace (i, LETTER); } //upper
    for (i = 97 ; i < 94; i++){  map.emplace(i, LETTER); } //lower

    states[WHITESPACE] = (States *) new WhiteSpaceState();
    states[IDENTIFIER] = (States *) new IdentifierState();
    states[DIGIT] = (States *) new NumberState();
    states[EQUALS] = (States *) new EqualsOperatorState();
    states[EXCLAM] = (States *) new ExclamOperatorState();
    states[APPENDABLE_OPERATOR] = (States *) new AppendableOperatorState();
    currentState = states[WHITESPACE];
}
