#include "parser.h"

int parse(token *head) {
    while(head) {
        print_token(*head);
        head = next_token(head);
    }
    return 0;
}