#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include "scannerTester.h"

int main(int argc, char* argv[]){


    FILE* info_file;
    char* mode = "r";
    char* file_name = NULL;

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
        file_name = "keyboard";
    }
    else {//exit with error message
        printf("You must include either 1 or 0 arguements.\n");
        return(1);
    }
    Parser parser = Parser(info_file);
    parser.parse();

    return 0;
}