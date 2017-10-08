//
// Created by jamy on 10/7/17.
//

#include <cstdio>
#include <cstdlib>
#include "scannerTester.h"

void Parser::parse() {
    do {
        if (array_elements + 1 > array_size) {
            token_array = (token *) (realloc(token_array, array_size + 100));
            array_size += 100;
        }

        token_array[array_elements] = scanner.getToken();
        printf("%s %s\n", token_array[array_elements].name, token_array[array_elements].value);
    } while (token_array[array_elements++].id != EOF_tkn);
    return;
}

Parser::Parser(FILE *source_file):
        scanner(Scanner(source_file)),
        source_file (source_file){}