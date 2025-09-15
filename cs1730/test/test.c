#include <stdio.h>

struct student {
    char * firstName; //8
    char * lastName; //8
    int id; //4
    double gpa; //8
};

struct group { // 8 byte aligned
    struct student s1[4]; // 4*8 = 128
    unsigned short groupId; //2
    char groupLetter; //1
    double averageGpa; //8
};

struct group2 { // 8 byte aligned
    struct student s1[4];//4*32=128
    unsigned short groupId; //2
    double averageGpa; //8
    char groupLetter; //1
};

int main() {
    struct student s;
    struct student * sp;
    struct group g;
    struct group2 g2;
    printf("%ld\n", sizeof(s)); // 32
    printf("%ld\n", sizeof(sp)); // 8
    printf("%ld\n", sizeof(g)); // 144 = 128 + 2 + 1 + 5(padding for double) + 8
    printf("%ld\n", sizeof(g2)); // 152 = 128 + 2 + 6 (padding for double) + 8 + 1 + 7 (padding for group 2)
    return 0;
}
