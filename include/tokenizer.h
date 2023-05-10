#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdio.h>

enum token_type {
    IDENTIFIER,
    KEYWORD,
    SEPARATOR,
    OPERATOR,
    LITERAL,
    COMMENT
};

typedef struct token_t {
    enum token_type type;
    char value[255];
    struct token_t *next;
} token;

token * tokenize(char *filename);

#endif