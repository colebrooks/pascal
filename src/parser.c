#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"

static token *current = NULL;

bool match_and_consume(token_type type) {
    return false;
}

void next_token(token **current) {
    token *next = (*current)->next;
    free(*current);
    *current = next;
}

void parse_program_statement() {

}

int parse(token *head) {
    current = head;
    while(current) {
        print_token(*current);
        // parse_program_statement();
        next_token(&current);
    }
    return 0;
}