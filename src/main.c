#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please input a file to parse.\n");
        return 1;
    } else {
        token *head = tokenize(argv[1]);
        parse(head);
    }
    return 0;
}