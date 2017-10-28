//
// Created by jamy on 10/7/17.
//

#include <cstdio>
#include "scannerTester.h"

void Parser::parse() {
    do {

        currentToken = scanner.getToken();
        printf("%-18s %-11s %d\n", token_names[currentToken.id], currentToken.value, currentToken.line);
    } while (currentToken.id != EOF_tkn && currentToken.id != ERR_tkn);
    return;
}

Parser::Parser(FILE *source_file):
        scanner(Scanner(source_file)){}