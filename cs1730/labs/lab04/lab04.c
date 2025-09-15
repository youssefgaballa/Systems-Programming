#include <stdio.h> //printf
#include <string.h> // strlen, strcmp
#include <stdlib.h> //atoi,atol

/*
 * Takes a string as input and then converts it to
 * an unsigned long int which is returned by the function.
 */
unsigned long int toInt(char * num);

/*
 * Converts num to binary then prints the
 * binary representation of num.
 */
void printBinary(unsigned long int num, int length);

/*
 * Prints the string num (assumed to be in binary) with
 * the specified length number of characters
 * padding it with 0's if it is too short.
 */
void printBits(char * num, int length);

/*
 * Performs the bitwise NOT operation on charNum (assumed to be binary)
 * and prints the result in binary and in base 10.
 */
void printNOT(char * charNum, int length);

/*
 * Performs the bitwise shift operation specified by the shift parameter
 * and prints the result in binary while preserving the length of the longest
 * charNum, then prints the result in base 10.
 */
void printShift(char * charNum1, char * charNum2, char shift, int length);

/*
 * Converts num to decimal with length number of binary digits,
 * with any digits in positions greater than length having a value of 0.
 */
unsigned long int toDecimal(unsigned long int num, int length);

/*
 * Processes the command line args, performs the specified bit wise operation
 * then prints the result in bitwise form with each number having the length of
 * the longest argument, and prints it in base 10.
 */
int main(int argc, char * argv[]) {
    int length;
    if (strcmp(argv[1], "-not") == 0) {
        length = strlen(argv[2]);
        printNOT(argv[2], length);
    } else {
        char * operationStr = argv[2];
        length = (strlen(argv[1]) > strlen(argv[3])) ? strlen(argv[1]) : strlen(argv[3]);
        if (strcmp(operationStr, "-leftshift") == 0) {
            printShift(argv[1], argv[3], '<', length);
        } else if (strcmp(operationStr, "-rightshift") == 0) {
            printShift(argv[1], argv[3], '>', length);
        }
    }

}

void printShift(char * charNum1, char * charNum2, char shift, int length) {
    unsigned long int num1 = toInt(charNum1);
    unsigned long int num2 = atol(charNum2);

    if (shift == 60 ) { // '<' == 60 in anscii
        unsigned long int result = num1 << num2;
        printBits(charNum1, length);
        printf(" << ");
        printBinary(num2, length);
        printf(" evaluates to ");
        printBinary(result, length);
        printf(" using bit strings of length %d\n", length);
        printf("%lu << %lu evaluates to %lu using bit unsigned %d-bit integers\n", num1, num2, toDecimal(result, length), length);
    } else if (shift == 62) { // '>' == 62 in anscii
        unsigned long int result = num1 >> num2;
        printBits(charNum1, length);
        printf(" >> ");
        printBits(charNum2, length);
        printf(" evaluates to ");
        printBinary(result, length);
        printf(" using bit strings of length %d\n", length);
        printf("%lu >> %lu evaluates to %lu using bit unsigned %d-bit integers\n", num1, num2, toDecimal(result, length), length);
    }

}

unsigned long int toDecimal(unsigned long int num, int length) {
     _Bool bit[64] = {0};
    int index = 0;
    unsigned long int flag = 1;
    for (; index < length; index++, flag = flag << 1) {
        if ((flag & num) == flag) {
            bit[index] = 1;
        }
    }
    unsigned long int result = 0;
    index = 0;
    unsigned long int power = 1;
    for (; index < length; index++, power *=2) {
        if (bit[index]) {
            result += power;
        }
    }
    return result;
}

void printNOT(char * charNum, int length) {
    unsigned long int num = toInt(charNum);
    unsigned long int result = ~num;
    printf("~");
    printBits(charNum, length);
    printf(" evaluates to ");
    printBinary(result, length);
    printf(" using bit strings of length %d\n", length);
    printf("~%lu evaluates to %lu using bit unsigned %d-bit integers\n", num, toDecimal(result, length), length);

}

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
    for (; index >=0; index--, power *=2) {
        if (bit[index]) {
            result += power;
        }
    }
    return result;
}

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
    bitIndex = length - 1;

    for (int i = bitIndex; i>= 0; i--) {
        printf("%d", bit[i]);
    }
}

void printBits(char * num, int length) {
    int difference = length - strlen(num);

    for (int i = 0; i < difference; i++) {
        printf("%d", 0);
    }

    printf("%s", num);
}
