#include <stdio.h> // printf
#include <stdlib.h> //atoi, atol
#include <string.h> //strlen(), strcmp()

/*
 * Takes two numbers represented as strings, a length, and an operation.
 * This method converts the numbers to long unsigned ints, performs the
 * operation, then prints the result in base 10 and binary with the binary
 * representation having the same number of digits as the num with the largest
 * length.
 */
void printBitOp(char * charNum1, char * charNum2, int length, char Operation);

/*
 * Performs the printBitOp using the command line arguments, argv[1] being the
 * first int, argv[3] being the second, and argv[2] being the operation.
 */
int main(int argc, char * argv[]) {
    int length = (strlen(argv[1]) > strlen(argv[3])) ? strlen(argv[1]) : strlen(argv[3]);
    char * operationStr = argv[2];
    if (strcmp(operationStr, "-and") == 0) {
        printBitOp(argv[1], argv[3], length, '&');
    } else if (strcmp(operationStr, "-or") == 0) {
        printBitOp(argv[1], argv[3], length, '|');
    } else if (strcmp(operationStr, "-xor") == 0) {
        printBitOp(argv[1], argv[3], length, '^');
    }
    return 0;
}

/*
 * Takes a string as input and then converts it to
 * an unsigned long int which is returned by the function.
 */
unsigned long int toInt(char * num) {
    _Bool bit[64] = {0};
    int index = 0;
    for (; *num != '\0'; index++, num++) {
        if (*num == 48) {  // 48 = '0' in anscii
            bit[index] = 0;
        } else if (*num == 49) {  // 49 = '1' in anscii
            bit[index] = 1;
        }
    }
    unsigned long int result = 0;
    index--;
    unsigned long int power = 1;
    for (int i = 0; index >=0; index--, i++, power *=2) {
        if (bit[index]) {
            result += power;
        }
    }
    return result;
}

/*
 * Prints the binary representation of num and
 * padding it with 0's if its length is less than
 * the length argument.
 */
void printBinary(unsigned long int num, int length) {
    _Bool bit[64] = {0};
    unsigned long int quotient = num;
    int remainder = 0;
    int bitIndex = 0;
    while (quotient > 0) {
        remainder = quotient % 2;
        quotient = quotient / 2;
        bit[bitIndex] = remainder;
        bitIndex++;
    }
    bitIndex--;
    int difference = length - bitIndex - 1;
    for (int i = 0; i < difference; i++) {
        printf("%d", 0);
    }
    for (int i = bitIndex; i>= 0; i--) {
        printf("%d", bit[i]);
    }
}

/*
 * Prints num (assumed to be in binary) with
 * the specified length number of characters,
 * padding it with 0's if it is too short
 */
void printBits(char * num, int length) {
    int difference = length - strlen(num);

    for (int i = 0; i < difference; i++) {
        printf("%d", 0);
    }

    printf("%s", num);
}



void printBitOp(char * charNum1, char *  charNum2, int length, char operation) {
    unsigned long int result;
    unsigned long int num1 = toInt(charNum1);
    //printf("Num1: %lu", num1);
    unsigned long int num2 = toInt(charNum2);
    //eprintf("Num2: %lu", num2);
    if (operation == 38) { // 38 = '&' in anscii
        result = num1 & num2;
    } else if (operation == 124) { // 124 = '|' in anscii
        result = num1 | num2;
    } else if (operation == 94) { // 94 = '^' in anscii
        result = num1 ^ num2;
    }

    printBits(charNum1, length);
    printf(" %c ", operation);
    printBits(charNum2, length);
    printf(" evaluates to ");
    printBinary(result, length);
    printf(" using bit strings of length %d\n", length);
    printf("%lu %c %lu evaluates to %lu using unsigned %d-bit integers\n",
           num1, operation, num2, result, length);
}
