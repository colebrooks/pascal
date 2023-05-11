#include "parser.h"

int parse(token *head) {
    token *current = head;
    while(current != NULL) {
        print_token(*current);
        current = next_token(current);
    }
    return 0;
}