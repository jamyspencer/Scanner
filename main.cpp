#include <cstdio>
#include <cstring>

#include "State.h"
#include "main.h"

int main(int argc, char* argv[]) {

    States states = States();
    states.white = new WhiteSpaceState();
    states.identifier = new IdentifierState();
    states.number = new NumberState();
    states.operatr = new OperatorState();

    State* currentState = states.white;
    char buffer[BUFSIZE] = {'\0'};
    char value;

    FILE* info_file;
    char mode = 'r';
    char* file_name = NULL;

    if (argc == 2){ //1 parameter given
        info_file = fopen(argv[1], &mode);
        if (info_file == NULL){
            printf("ERROR: unable to open file %s\n", argv[1]);
            return 1;
        }
    }
    else {
        printf("ERROR: need an additional file parameter\n");
    }

    while(true){
        value = fgetc(info_file);
        currentState = currentState->evaluate(value, buffer, &states);
        if (currentState == NULL) {
            return -1;
        }

    }

    return 0;
}