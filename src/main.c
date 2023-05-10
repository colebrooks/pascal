#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please input a file to parse.\n");
        return 1;
    } else {
        token *tok = tokenize(argv[1]);
        while(tok != NULL) {
            print_token(*tok);
            tok = tok->next;
        }
    }
    return 0;
}