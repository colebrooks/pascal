#include <stdio.h>

#include "token_types.h"

typedef struct token_t {
    enum token_type type;
    char value[];
} token;

token next_token();
void tokenize(FILE *fp);