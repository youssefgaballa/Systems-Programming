#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Decodes the num parameter with length number of characters
 * in the decompression.
 */
void decompress(unsigned char num, int length) {
    //printf("%d\n", num);
    char* result = calloc(length + 1, 1);
    unsigned char A = 0;   // 0000 0000
    unsigned char T = 64;  // 0100 0000
    unsigned char C = 128; // 1000 0000
    unsigned char G = 192; // 1100 0000

    for (int i = 0; i < length; i++, A = A >> 2, T = T >> 2, C = C >> 2, G = G >> 2) {
        if ((~num & G) == G) { // Testing if the two bits encode A
            result[i] = 'A';
            //printf("%c\n", result[i]);
        } else if ((~num & C) == C) { // Testing them for T
            result[i] = 'T';
            //printf("%c\n", result[i]);
        } else if ((~num & T) == T) { // for C
            result[i] = 'C';
            //printf("%c\n", result[i]);
        } else if ((num & G) == G) { // For G
            result[i] = 'G';
            //printf("%c\n", result[i]);
        }
    }
    result[length] = '\0';
    printf("%s", result);
}
