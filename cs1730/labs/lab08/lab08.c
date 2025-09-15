#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int * p = NULL;

/*
 * Return the sum of the n values in x starting at index 0.
 * If x is NULL, then return -1.
 * If n is 0 and x is not NULL, then return 0.
 */
int sum(int * x, int n);

int main(int argc, char * argv[]){
    // x should point to a new array of ints stored on the heap
    int * x = (int *) malloc(argc*sizeof(int));

    for(int i = 0; i < argc - 1; i++){
        x[i] = atoi(argv[i + 1]);
    }

    printf("*x is %d\n", *x);
    int y = sum(x, argc - 1);
    printf("y is %d\n", y);
    int z = sum(p, argc - 1);
    printf("z is %d\n", z);
    free(x);
    return 0;
}

int sum(int * x, int n){
    int sum = 0;
    if (x == NULL) {
        return -1;
    } else if (n == 0) {
        return 0;
    } else{
        for(int i = 0; i < n; i++){
            sum = sum + x[i];
        }
        return sum;
    }
}
