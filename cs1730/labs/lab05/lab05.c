#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Returns the integer representation of charNum with length number of bits
 */
long int toDecimal(char * charNum, int length);

/*
 * Prints the binary representation of num with length number of bits.
 */
void printBinary(long int num, int length);

/*
 * If the argument is -binary, the binary digit is converted to decimal and printed.
 * If the arguments are -bits and -decimal, the decimal is converted to binary with
 * the number of digits specified by the argument after -bits, then it is printed.
 */
int main(int argc, char * argv[]) {
    char * num;
    int length;
    if (argc == 5) {
        if (strcmp(argv[1], "-decimal") == 0) {
            num = argv[2];
            length = atoi(argv[4]);
        } else if (strcmp(argv[1], "-bits") == 0) {
            num = argv[4];
            length = atoi(argv[2]);
        }
        printf("%s in decimal is equal to ", num);
        printBinary(atol(num), length);
        printf(" in binary using %d-bit two's complement representation\n", length);

    } else if (argc == 3) {
        num = argv[2];
        length = strlen(num);
        // TODO: Fix this line please.
        printf("%s in binary is equal to ", num);
        printf("%ld", toDecimal(num, length));
        printf(" in decimal using %d-bit two's complement representation\n", length);
    }


    return 1;
}

long int toDecimal(char * charNum, int length) {
    long int result = 0;
    if (*charNum == 49) { // '1' == 49 in anscii - negative case
        // loop that goes to the end of the binary string
        for (; *charNum != '\0'; charNum++) {
        }
        charNum--;
        long int flag = 1;
        int i = 0;
        for (; i < length; i++, charNum--, flag=flag<<1) {
            if (*charNum == 49) { // *charNum == '1'
                result = (result | flag);
            }
        }
        for(; i < 64; i++, flag = flag << 1) {
            result = (result | flag);
        }
    } else { // positive case
        // loop that goes to the end of the binary string
        for (; *charNum != '\0'; charNum++) {
        }
        charNum--;
        long int power = 1;
        for (int i = 0; i < length; i++, charNum--, power*=2) {
            if (*charNum == 49) { // *charNum == '1'
                result+=power;
            }
        }
    }
    return result;

}

void printBinary(long int num, int length) {
    _Bool bit[64] = {0};

    long int flag = 1;
    for (int i = 0; i < length; i++, flag = flag<<1) {
        if ((flag & num) == flag) {
            bit[i] = 1;
        }
    }
    for (int i = length - 1; i >=0; i--) {
        if (bit[i]) {
            printf("%d", 1);
        } else {
            printf("%d", 0);
        }
    }

}
