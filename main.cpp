#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include "State.h"

int main(int argc, char* argv[]) {

    States states = States();
    State* currentState = states.white;
    char buffer[32] = {'\0'};
    char value;

    FILE* info_file;
    char mode = 'r';
    char* file_name = NULL;

    if (argc == 2){ //1 parameter given
        strcpy(file_name, argv[1]);
        info_file = fopen(file_name, &mode);
        if (info_file == NULL){
            printf("ERROR: unable to open file %s\n", argv[1]);
            return 1;
        }
    }
    else {
        printf("ERROR: need an additional file parameter\n");
    }

    while(!feof(info_file)){
        value = fgetc(info_file);
        currentState = currentState->evaluate(value, buffer, &states);

    }

    return 0;
}