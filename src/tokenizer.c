#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tokenizer.h"

const char *keywords[] = {"program", "function", "integer", "longint", "begin", "if", "then", "else", "end", "var", "for", "to", "do", "writeln"};
const char *separators[] = {";", "(", ")", ",", "'"};
const char *operators[] = {"+", "-" , "*" , "/", "%", "=", "<>", "<", ">", "<=", ">=", ":="};
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
            strcpy(type, "SEPARATOR");
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

void read_word(FILE *fp, char *val) {
    char buff[255] = "";
    char c;
    int len = 0;

    while(isalpha((c = fgetc(fp)))) {
        buff[len++] = c;
    }
    ungetc(c, fp);  // Unget final nonalpha char
    strcpy(val, buff);
}

token match_word(char val[]) {
    token tok;
    strcpy(tok.value, val);

    int len = sizeof(keywords) / sizeof(keywords[0]);
    int keyword = 0;
    for(int i = 0; i < len; i++) {
        if(!strcmp(val, keywords[i])) {
            keyword = 1;
            break;
        }    
    }
    tok.type = keyword ? KEYWORD : IDENTIFIER;
    return tok;
}

void read_num(FILE *fp, char *val) {
    char buff[255] = "";
    char c;
    int len = 0;

    while(isdigit(c = fgetc(fp))) {
        buff[len++] = c;
    }
    ungetc(c, fp);  // Unget final nondigit char
    strcpy(val, buff);
}

token match_num(char *val) {
    token tok;
    strcpy(tok.value, val);
    tok.type = LITERAL;
    return tok;
}

void read_sym(FILE *fp, char *val) {
    char buff[255] = "";
    char c;
    int len = 0;
    c = fgetc(fp);
    buff[len++] = c;
    if(c == '<' || c == '>' || c == '*' || c == ':' || c == '+' || c == '-' || c == '/' || c == '(' || c == '.') {
        c = fgetc(fp);
        if(c != ' ' && c != '\t' && c != '\n' && !isalpha(c) && !isdigit(c)) {
            buff[len++] = c;
        }
    }
    strcpy(val, buff);
}

token match_sym(char *val) {
    token tok;
    strcpy(tok.value, val);
    int operator = 0;

    int len = sizeof(operators) / sizeof(operators[0]);
    for(int i = 0; i < len; i++) {
        if(!strcmp(val, operators[i])) {
            operator = 1;
        }
    }
    tok.type = operator ? OPERATOR : SEPARATOR;
    return tok;
}

token match_token(FILE *fp) {
    char c = peek(fp); 
    while(c == ' ' || c == '\t' || c == '\n') {
        fgetc(fp);
        c = peek(fp);
    }
    
    char val[255] = "";
    token ret;
    if(isalpha(c)) {
        read_word(fp, val);
        ret = match_word(val);
    } else if(isdigit(c)) {
        read_num(fp, val);
        ret = match_num(val);
    } else {
        read_sym(fp, val);
        ret = match_sym(val);
    }
    print_token(ret);
    return ret;
}

void tokenize(FILE *fp) {
    int current_token = 0;
    while (!feof(fp)) {
        tokens[current_token++] = match_token(fp);
    }
} 
