//
// Created by jamy on 10/4/17.
//

#include <cstdio>
#include <cstdlib>
#include "scannerTester.h"
#include "scanner.h"
#include "Token.h"

int main(int argc, char* argv[]) {
    int array_size = 100;
    int array_elements = 0;
    Token* token_array = (Token*) malloc (sizeof(Token) * array_size);


    if (argc != 2){
        printf("ERROR: need an additional file parameter\n");
        return -1;
    }
    if (openFile(argv[1]) == false) {return -1;}

    do{

        if (array_elements + 1 > array_size){
            token_array = (Token*) (realloc(token_array, array_size + 100));
            array_size  += 100;
        }

        token_array[array_elements] = getToken();
        printf("%s %s\n", token_array[array_elements].name, token_array[array_elements].value);
    }while(token_array[array_elements++].id != EOF_tkn);
    return 0;
}