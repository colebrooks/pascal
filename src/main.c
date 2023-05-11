#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "parser.h"
#include "generator.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please input a file to parse.\n");
        return 1;
    } else {
        token *head = tokenize(argv[1]);
        if(parse(head) < 0) {
            goto parse_err;
        }
        if(generate() < 0) {
            goto generate_err;
        }
    }

    return 0;

    parse_err:
        fprintf(stderr, "Error: Parse error.\n");
        return -1;

    generate_err:
        fprintf(stderr, "Error: Generation error\n");
        return -2;

}