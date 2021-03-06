#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include "Parser.h"
#include "Assembler.h"


int main(int argc, char* argv[]){


    FILE* info_file;
    const char* mode = "r";
    char* file_name = nullptr;
    Node* treeRoot = nullptr;

    if (argc == 2){ //1 parameter given
        file_name = (char*) malloc (sizeof(char) * (strlen(argv[1]) + 5));
        strcpy(file_name, argv[1]);
        strcat(file_name, ".fs17");
        info_file = fopen(file_name, mode);
        if (info_file == NULL){
            printf("ERROR: unable to open file %s\n", argv[1]);
            return 1;
        }
        strcpy(file_name, argv[1]);
    }
    else if (argc == 1){//no parameters given
        info_file = stdin;
        file_name = (char*) malloc (sizeof(char) * 9);
        strcpy(file_name, "out");
    }
    else {//exit with error message
        printf("You must include either 1 or 0 arguements.\n");
        return(1);
    }
    Parser parser = Parser(info_file);
    treeRoot = parser.parse();
    treeRoot->reduceTree(0);
    treeRoot->traversePreOrder();
    std::string outFileName = std::string(argv[1])+ ".asm";
    Assembler assembler = Assembler(outFileName);
    assembler.assemble(treeRoot);
    return 0;
}