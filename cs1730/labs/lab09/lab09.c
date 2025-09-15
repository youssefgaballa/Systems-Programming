#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/*
 * Contains the encoding for a 32 bit float.
 */
struct floatEncoding {
    char sign[1];
    char exponent[9];
    char fraction[24];
};

/*
 * Contains the encoding for a 64 bit double.
 */
struct doubleEncoding {
    char sign[1];
    char exponent[12];
    char fraction[53];
};

/*
 * Returns the string-binary representation of the 32 bit int num.
 */
char* intToBinary(int num, int length);

/*
 * Returns the string-binary representation of the 64 bit long int num.
 */
char* longToBinary(long int num, int length);

/*
 * Puts the float encodings of numStr which is the binary representation of a 32 bit int into
 * the encoding struct.
 */
void getFloatEncodings(char * numStr, int length, struct floatEncoding * encoding);

/*
 * Puts the double encodings of numStr which is the binary representation of a 64 bit long int into
 * the encoding struct.
 */
void getDoubleEncodings(char * numStr, int length, struct doubleEncoding * encoding);

/*
 * Represents a 32 bit block of memory occupied by float f and int i.
 */
union floatIntUnion {
    float f;
    int i;
};

/*
 * Represents a 64 bit block of memory occupied by double d and long int l.
 */
union doubleLongUnion {
    double d;
    long int l;
};

/*
 * Process the command line arguments and displays the binary representation of
 * argv[2] as well as its double/float binary encodings.
 */
int main(int argc, char * argv[]) {
    char * binary = NULL;

    if (strcmp(argv[1],"-f") == 0) {
        struct floatEncoding encoding;
        union floatIntUnion fUnion;
        fUnion.f = (float) atof(argv[2]);
        binary = intToBinary(fUnion.i, 32);
        printf("%f encoded in binary using a 32 bit IEEE 754 encoding is below.\n", fUnion.f);
        printf("%s\n", binary);
        //printf("%-ld-\n", strlen(binary));
        getFloatEncodings(binary, 32, &encoding);
        printf("sign bit:          ");
        printf("%c\n", encoding.sign[0]);
        printf("exponent (%ld bit):  ", strlen(encoding.exponent));
        printf("%s\n", encoding.exponent);
        printf("fraction (%ld bit): ", strlen(encoding.fraction));
        printf("%s\n", encoding.fraction);

    } else if (strcmp(argv[1],"-d") == 0) {
        struct doubleEncoding encoding;
        union doubleLongUnion dUnion;
        dUnion.d = (double) atof(argv[2]);
        //printf("- %ld -\n", dUnion.l);
        binary = longToBinary(dUnion.l, 64);
        printf("%lf encoded in binary using a 64 bit IEEE 754 encoding is below.\n", dUnion.d);
        printf("%s\n", binary);
        //printf("%-ld-\n", strlen(binary));
        getDoubleEncodings(binary, 64, &encoding);
        printf("sign bit:          ");
        printf("%c\n", encoding.sign[0]);
        printf("exponent (%ld bit): ", strlen(encoding.exponent));
        printf("%s\n", encoding.exponent);
        printf("fraction (%ld bit): ", strlen(encoding.fraction));
        printf("%s\n", encoding.fraction);

    }
    free(binary);
    return 0;
}

void getDoubleEncodings(char * numStr, int length, struct doubleEncoding * encoding) {
    int index = 0;
    encoding->sign[0] = *numStr;
    index++;
    numStr++;
    int size1 = 12;
    for (int i = 0; (index < size1) && (*numStr != '\0'); i++, index++, numStr++) {
        if (*numStr == 49) { // 1
            encoding->exponent[i] = '1';
        } else if (*numStr == 48) { // 0
            encoding->exponent[i] = '0';
        }
     }
     encoding->exponent[size1] = '\0';
     for (int i = 0; (index < length) && (*numStr != '\0'); i++, index++, numStr++) {
         if (*numStr == 49) { // 1
             encoding->fraction[i] = '1';
         } else if (*numStr == 48) { // 0
             encoding->fraction[i] = '0';
         }
     }
     encoding->fraction[length - size1] = '\0';
}


void getFloatEncodings(char * numStr, int length, struct floatEncoding * encoding) {
    int index = 0;
    encoding->sign[0] = *numStr;
    index++;
    numStr++;
    int size1 = 9;
    for (int i = 0; (index < size1) && (*numStr != '\0'); i++, index++, numStr++) {
        if (*numStr == 49) { // 1
            encoding->exponent[i] = '1';
        } else if (*numStr == 48) { // 0
            encoding->exponent[i] = '0';
        }
     }
     encoding->exponent[size1] = '\0';
     for (int i = 0; (index < length) && (*numStr != '\0'); i++, index++, numStr++) {
         if (*numStr == 49) { // 1
             encoding->fraction[i] = '1';
         } else if (*numStr == 48) { // 0
             encoding->fraction[i] = '0';
         }
     }
     encoding->fraction[length - size1] = '\0';
}

char* intToBinary(int num, int length) {

    char * binary = (char *) malloc(sizeof(char) * length + sizeof(char));
    char * ptrCopy = binary;
    int index = 0;
    for (; index < length - 1; index++, ptrCopy++) {
    }
    ptrCopy++;
    *ptrCopy = '\0';
    ptrCopy--;
    int cmp = 1;
    for (; index >= 0; index--, ptrCopy--, cmp = cmp << 1) {
        if ((num & cmp) == cmp) {
            *ptrCopy = 49; // '1' = 49

        } else {
            *ptrCopy = 48; // '0' = 48
        }
        //printf("%c-", *ptrCopy);
    }

    return binary;
}

char* longToBinary(long int num, int length) {

    char * binary = (char *) malloc(sizeof(char) * length + sizeof(char));
    char * ptrCopy = binary;
    int index = 0;
    for (; index < length - 1; index++, ptrCopy++) {
    }
    ptrCopy++;
    *ptrCopy = '\0';
    ptrCopy--;
    long int cmp = 1;
    for (; index >= 0; index--, ptrCopy--, cmp = cmp << 1) {
        if ((num & cmp) == cmp) {
            *ptrCopy = 49; // '1' = 49

        } else {
            *ptrCopy = 48; // '0' = 48
        }
        //printf("%c-", *ptrCopy);
    }

    return binary;
}
