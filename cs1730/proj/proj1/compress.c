#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Compresses str into its associated 8 bit integral type
 */
unsigned char compress(char * str) {
    unsigned char result = 0; // 0000 0000
    unsigned char A = 0;   // 0000 0000
    unsigned char T = 64;  // 0100 0000
    unsigned char C = 128; // 1000 0000
    unsigned char G = 192; // 1100 0000
    for (int i = 0; (*str != '\0') && (i < 4) ; i++, str++, T = T >> 2, C = C >> 2, G = G >> 2) {
        //printf("%c\n", *str);
        if (*str == 65) { // 65 == 'A'
            result = result | A;
        } else if (*str == 84) { // 84 == 'T'
            result = result | T;
        } else if (*str == 67) { // 67 == 'C'
            result = result | C;
        } else if (*str == 71) { // 71 == 'G'
            result = result | G;

        }
    }
    //printf("-%d-", result);
    return result;

}

/*
 * Prints each compression integer from str
 * with length number of characters
 */
void printCompression(char * str, int length) {
    printf("%d ", length);
    int size;
    if(length % 4 == 0) {
        size = length / 4;
    } else {
        size = (length / 4) + 1;
    }
    for (int i = 0; i < size; i++, str=str+4) {
        printf("%d ", compress(str));
    }
}
