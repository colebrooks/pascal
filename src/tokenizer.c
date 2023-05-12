#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "tokenizer.h"

const char *keywords[] = {"program", "function", "integer", "longint", "begin", "if", "then", "else", "end", "var", "for", "to", "do", "writeln", "while"};
const char *separators[] = {";", "(", ")", ",", "."};
const char *operators[] = {"+", "-" , "*" , "/", "%", "=", "<>", "<", ">", "<=", ">=", ":=", "+=", "-=", "*=", "/="};
const char double_syms[] = {'<', '>', '*', ':', '+', '-', '/', '(', '.'};
token *head = NULL;
token *current = NULL;
int num_tokens = 0;
int line = 1;

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
    printf("Token Type: %-15s Token Value: %-15s Line: %d\n", type, tok.value, tok.line);
}

token *next_token(token *current) {
    if(!current->next) return NULL;
    token *next = current->next;
    free(current);
    return next;
}

char peek(FILE *fp) {
    char c;
    c = fgetc(fp);
    ungetc(c, fp);
    return c;
}

bool double_symbol(char c) {
    int len = sizeof(double_syms) / sizeof(double_syms[0]);
    for(int i = 0; i < len; i++) {
        if(c == double_syms[i]) {
            return true;
        }
    }
    return false;
}

bool separator(char *val) {
    int len = sizeof(separators) / sizeof(separators[0]);
    for(int i = 0; i < len; i++) {
        if(!strcmp(val, separators[i])) {
            return true;
        }
    }
    return false;
}

bool operator(char *val) {
    int len = sizeof(operators) / sizeof(operators[0]);
    for(int i = 0; i < len; i++) {
        if(!strcmp(val, operators[i])) {
            return true;
        }
    }
    return false;
}

bool keyword(char *val) {
    int len = sizeof(keywords) / sizeof(keywords[0]);
    for(int i = 0; i < len; i++) {
        if(!strcmp(val, keywords[i])) {
            return true;
        }
    }
    return false;
}
 
void consume_whitespace(FILE *fp) {
    char c = peek(fp);
    while(c == ' ' || c == '\t' || c == '\n') {
        fgetc(fp);
        if(c == '\n') line++;
        c = peek(fp);
    }
}

token new_token(token_type type, char *val) {
    token tok;
    tok.type = type;
    tok.line = line;
    strcpy(tok.value, val);
    tok.next = NULL;
    return tok;
}

token read_word(FILE *fp) {
    // TODO: Rework to make more elegant, prevent reading of EOF as word
    char buff[255] = "";
    char c;
    int len = 0;

    while(isalpha((c = fgetc(fp)))) {
        buff[len++] = c;
    }
    ungetc(c, fp);  // Unget final nonalpha char

    token_type type = keyword(buff) ? KEYWORD : IDENTIFIER;
    return new_token(type, buff);
}

token read_num(FILE *fp) {
    // TODO: Implement floats
    char buff[255] = "";
    char c;
    int len = 0;

    while(isdigit(c = fgetc(fp))) {
        buff[len++] = c;
    }
    ungetc(c, fp);  // Unget final nondigit char

    return new_token(LITERAL, buff);
}

void read_string(FILE *fp, char *val) {
    char buff[255] = "";
    char c;
    int len = 0;
    // TODO: Add single quote escape to strings
    buff[len++] = '\'';
    while((c = fgetc(fp)) != '\'')  {
        buff[len++] = c;
    }
    buff[len++] = c;
    strcpy(val, buff);
}

void read_double_sym(FILE *fp, char *val, char c) {
    char buff[2] = "";
    buff[0] = c;
    char next = peek(fp);
    switch(c) {
    case '<' : 
    case '>' :
        if(next == '<' || next == '>' || next == '=') {
            c = fgetc(fp);
            buff[1] = c;
        }
        break;
    case '*' :
        if(next == '*' || next == '=' || next == ')') {
            c = fgetc(fp);
            buff[1] = c;
        }
        break;
    case ':' :
    case '+' :
    case '-' :
        if(next == '=') {
             c = fgetc(fp);
             buff[1] == c;
        }
        break;
    case '/' :
        if(next == '=' || next == '/') {
            c = fgetc(fp);
            buff[1] = c;
        }
        break;
    case '(' :
        if(next == '*' || next == '.') {
            c = fgetc(fp);
            buff[1] = c;
        }
        break;
    case '.' :
        if(next == ')') {
            c = fgetc(fp);
            buff[1] = c;
        }
        break;
    }
    strcpy(val, buff);
}

token read_sym(FILE *fp) {
    // TODO: Add error handling for unknown symbols
    char buff[255] = "";
    char c;
    token_type type;

    c = fgetc(fp);
    if(c == '\'') {
        read_string(fp, buff);
    } else if(double_symbol(c)) {
        read_double_sym(fp, buff, c);
    } else {
        buff[0] = c;
    }

    if (buff[0] == '\'') {
        type = LITERAL;
    } else if (operator(buff)) {
        type = OPERATOR;
    } else if(separator(buff)) {
        type = SEPARATOR;
    }
    return new_token(type, buff);
}

token get_token(FILE *fp) {
    consume_whitespace(fp);
    token tok;
    char val[255] = "";
    char c = peek(fp);
    if(isalpha(c)) {
        tok = read_word(fp);
    } else if(isdigit(c)) {
        tok = read_num(fp);
    } else {
        tok = read_sym(fp);
    }
    return tok;
}

token *tokenize(char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    while (!feof(fp)) {
        token *new = (token *)malloc(sizeof(token));
        *new = get_token(fp);
        if(head == NULL) {
            head = new;
            current = head;
        } else {
            current->next = new;
            current = current->next;
        }
    }
    fclose(fp);
    return head;
}
