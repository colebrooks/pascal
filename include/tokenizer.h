#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdio.h>

typedef enum {
    IDENTIFIER,
    KEYWORD,
    SEPARATOR,
    OPERATOR,
    LITERAL,
    COMMENT
} token_type;

typedef struct token_t {
    token_type type;
    char value[255];
    struct token_t *next;
} token;

token *tokenize(char *);
void print_token(token);
token *next_token(token *);

#endif