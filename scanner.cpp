#include <cstdio>
#include <cstdlib>


#include "scanner.h"
#include "Token.h"

static States* states[7];
static States* currentState;

static FILE* info_file;
char value;


struct Token getToken() {
    struct Token token;
    token.value[0] = '\0';

    //this corrects the state due to look-aheads
    if (currentState == NULL ){
        currentState = states[WHITESPACE];
        currentState = currentState->driver[map[value + 1]](&value, &token, states);
    }else {
        currentState->isFinal = false;
    }
    //primary token generating loop
    while ( currentState != NULL && !currentState->isFinal ) {
        value = fgetc(info_file);
        currentState = currentState->driver[map[value + 1]](&value, &token, states);
    }

    return token;
}

bool openFile(char* file_name){
    char mode = 'r';
    info_file = fopen(file_name, &mode);
    if (info_file == NULL){
        printf("ERROR: unable to open file %s\n", file_name);
        return false;
    }
    states[WHITESPACE] = (States*) new WhiteSpaceState();
    states[IDENTIFIER] = (States*) new IdentifierState();
    states[DIGIT] = (States*) new NumberState ();
    states[EQUALS] = (States*) new EqualsOperatorState();
    states[EXCLAM] = (States*) new ExclamOperatorState();
    states[APPENDABLE_OPERATOR] = (States*) new AppendableOperatorState();
    currentState = states[WHITESPACE];
    return true;
}