#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi
#include <stdbool.h>
#include "compress.h"
#include "decompress.h"

/*
 * Processes the command line arguments and separates it into the
 * compression case and decompresison case.
 */
int main(int argc, char * argv[]) {
    char* flag = argv[1];
    if (strcmp(flag, "-c") == 0) {
        printCompression(argv[2], strlen(argv[2]));
    } else if (strcmp(flag, "-d") == 0) {
        int length = atoi(argv[2]);
        int count = argc - 3;
        int nums[count];
        for (int i = 0, j = 3; j < argc; i++, j++) {
            nums[i] = atoi(argv[j]);
        }
        int size;
        if (length % 4 != 0) {
            size = length % 4;
        } else {
            size = 4;
        }
        for (int i = 0; i < count - 1; i++) {
            decompress(nums[i],4);
        }
        decompress(nums[count - 1], size);

    }
    printf("\n");
    return 0;
}
