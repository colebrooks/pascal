#include <stdio.h>

#include "tokenizer.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please input a file to parse.\n");
        return 1;
    } else {
        FILE *fp;
        fp = fopen(argv[1], "r");
        tokenize(fp);
    }

    return 0;
}