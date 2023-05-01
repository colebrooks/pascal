#include <string.h>
#include <ctype.h>

#include "tokenizer.h"

const char *keywords[] = {"function", "integer", "longint", "begin", "if", "then", "else", "end", "var", "for", "to", "do", "writeln"};
token tokens[255];
int num_tokens = 0;

void print_token(token tok) {
    char type[255];
    switch(tok.type) {
        case 0: 
            strcpy(type, "IDENTIFIER");
            break;
        case 1:
            strcpy(type, "KEYWORD");
            break;
        case 2:
            strcpy(type, "SEPARTATOR");
            break;
        case 3:
            strcpy(type, "OPERATOR");
            break;
        case 4:
            strcpy(type, "LITERAL");
            break;
        case 5:
            strcpy(type, "COMMENT");
            break;
    }
    printf("Token Type: %s, Token Value: %s\n", type, tok.value);
}
 
char peek(FILE *fp) {
    char c;
    c = fgetc(fp);
    ungetc(c, fp);
    return c;
}

void read_word(FILE *fp, char *word) {
    char buff[255] = "";

    char c;
    int len = 0;
    while(isalpha((c = fgetc(fp)))) {
        buff[len++] = c;
    }
    strcpy(word, buff);
}

token match_word(char word[]) {
    token tok;
    strcpy(tok.value, word);

    int len = sizeof(keywords) / sizeof(keywords[0]);
    for(int i = 0; i < len; i++) {
        if(!strcmp(word, keywords[i])) {
            tok.type = KEYWORD;
            print_token(tok);
            return tok;
        }
    }
}

void read_tokens(FILE *fp) {
    int current_token = 0;
    char c;
    while (!feof(fp)) {
        char c = peek(fp);
        if(isalpha(c)) {
            char word[255];
            read_word(fp, word);
            tokens[current_token++] = match_word(word);
        } else {
            fgetc(fp);
        }
    }
}

void tokenize(FILE *fp) {
    read_tokens(fp);
} 
