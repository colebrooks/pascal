#include<string.h>

#include "tokenizer.h"

token tokens[255];

void tokenize(FILE *fp) {
    char buff[255];
    fgets(buff, 255, fp);

    int current_token = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s", buff);
        token token;
        strcpy(token.value, buff);
        tokens[current_token++] = token;
        printf("Token value: %s\n", token.value);
    }
} 
