#include <stdio.h>
#include <stdlib.h> // atoi

/*
 * Converts the two inputted integers to binary and prints the result.
 * Also calculates the hamming distance between the two and prints the result.
 */
void printBitStrings(unsigned long int num1, unsigned long int num2);

/*
 * Converts the two command line arguments to integers then calls
 * the printBitStrings function.
 */
int main(int argc, char * argv[]) {
    long int num1 = atol(argv[1]);
    long int num2 = atol(argv[2]);
    printBitStrings(num1, num2);
    return 0;
}

void printBitStrings(unsigned long int num1, unsigned long int num2) {
    _Bool bit1[64] = {0};
    _Bool bit2[64] = {0};
    unsigned long int quotient1 = num1;
    unsigned long int quotient2 = num2;
    int remainder1 = 0;
    int remainder2 = 0;
    int bitIndex1 = 0;
    int bitIndex2 = 0;

    while (quotient1 > 0) {
        remainder1 = quotient1 % 2;
        quotient1 = quotient1 / 2;
        bit1[bitIndex1] = remainder1;
        bitIndex1++;
    }
    while (quotient2 > 0) {
        remainder2 = quotient2 % 2;
        quotient2 = quotient2 / 2;
        bit2[bitIndex2] = remainder2;
        bitIndex2++;
    }
    int bitIndex = bitIndex1 > bitIndex2 ? bitIndex1 : bitIndex2;
    for (int i = bitIndex - 1; i >=0; i--) {
        printf("%d", bit1[i]);
    }
    printf(" is the bit string for %lu\n", num1);

    for (int i = bitIndex - 1; i >=0; i--) {
        printf("%d", bit2[i]);
    }
    printf(" is the bit string for %lu\n", num2);
    int hammingDist = 0;
    for (int i = bitIndex - 1; i >=0; i--) {
        if (bit1[i] ^ bit2[i]) {
            hammingDist++;
        }
    }
    printf("%d is the hamming distance between the bit strings\n", hammingDist);
}
