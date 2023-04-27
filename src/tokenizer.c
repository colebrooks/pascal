#include <string.h>
#include <ctype.h>

#include "tokenizer.h"

token tokens[255];
int num_tokens = 0;

void read_word(FILE *fp, char first_letter) {
    char word[255] = "";
    word[0] = first_letter;

    int len = 1;
    char c;
    while(isalpha((c = fgetc(fp)))) {
        word[len++] = c;
    }
    printf("Word: %s\n", word);
}

void read_tokens(FILE *fp) {
    int current_token = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if(isalpha(c)) {
            read_word(fp, c);
        }
    }
    if (feof(fp)) {
        return;
    } else {
        printf("Error reading tokens from file!\n");
        return;
    }
}

void tokenize(FILE *fp) {
    read_tokens(fp);
} 

