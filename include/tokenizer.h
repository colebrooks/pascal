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
} token;

token next_token();
void tokenize(FILE *fp);

#endif