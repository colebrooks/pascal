#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

// char *source = NULL;

// Potential fucture implementation of eager file reading
// void read_file(char *file) {
//     FILE *fp = fopen(file, "r");
//     if(fp != NULL) {
//         if (fseek(fp, 0L, SEEK_END) == 0) {
//             long bufsize = ftell(fp);
//             if (bufsize == -1) { /* Error */ }
// 
//             source = malloc(sizeof(char) * (bufsize + 1));
//             rewind(fp);
// 
//             size_t newLen = fread(source, sizeof(char), bufsize, fp);   
//             if (ferror(fp) != 0) { /* Error reading file */ }
//             else {
//                 source[newLen++] = '\0'; 
//             }
//         }
//     }
//     fclose(fp);
// }

int main(int argc, char *argv[]) {
    FILE *source;
    if(argc != 2) {
        printf("Please input a file to parse.\n");
        return 1;
    } else {
        source = fopen(argv[1], "r");
    }
    tokenize(source);
    return 0;
}