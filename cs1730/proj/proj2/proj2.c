#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Allowed functions: printf, scanf, malloc, free

double averageGrade(const double * ptr, int count);
double* copy(double * ptr, int count);
void compare(const double * ptr, int count, double average);

// represents the total number of bytes allocated
int bytes = 0;

/*
 * Processes inputted grades then computes the average of the grades.
 * The total allocs, frees, and allocated memory is shown at the end.
 */
int main() {
    printf("Enter a list of grades below where each grade is separated by a newline character.\n"
           "After the list of grades is entered, enter a negative value to end the list.\n");
    int allocs = 0;
    int frees = 0;

    double * ptr = NULL; // Points to first double (used for copying to other pointers)
    int count = 0;
    //  printf("Total heap usage: 0 allocs, 0 frees, 0 bytes allocated\n");
    double * ptrCopy = NULL;
    double num = 0;
    while (num >= 0) {
        ptrCopy = ptr + count;
        do {
            scanf("%lf", &num);
            if ((ptr == NULL) && (num >= 0)) {
                ptr = (double *) malloc(sizeof(double)*5); // Allocating memory for 5 doubles
                printf("Allocated 40 bytes to the heap at %p.\n", (void *)ptr);
                allocs++;
                bytes +=40;
                ptrCopy = ptr;
                *ptrCopy = num;
                printf("Stored %.6lf in the heap at %p.\n", num, (void *)ptrCopy);
                count++;
            } else if ((ptr == NULL) && (num < 0)) {

            } else {
                if (num >= 0) {
                    *ptrCopy = num;
                    printf("Stored %.6lf in the heap at %p.\n", num, (void *)ptrCopy);
                    //printf("--%lf--\n", *ptr1); //debug
                    count++;
                }
            }
            ptrCopy++;
        } while((count % 5 != 0) && (num >= 0));

        if ((count % 5 == 0) && (num >= 0)) {
            printf("Stored %d grades (%d bytes) to the heap at %p.\n", count, count*8, (void *) ptr);
            printf("Heap at %p is full.\n", (void *) ptr);
            ptr = copy(ptr, count); // creates
            allocs++;
            // bytes+= 40;
            frees++;
        } else if (count == 0) {
            printf("The average of %d grades is %.6lf.\n", count, 0.0);
            printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", allocs, frees, bytes);
        } else {
            double average = averageGrade(ptr, count);
            printf("The average of %d grades is %.6lf.\n", count, average);
            compare(ptr, count, average);
            free(ptr);
            frees++;
            printf("Freed %lu bytes from the heap at %p.\n", allocs*5*sizeof(double), (void *)ptr);
            printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", allocs, frees, bytes);
        }

    }
    //printf("Ending main\n"); // debug
    return 0;
}

/*
 * Creates a new pointer that can hold five more grades and
 * copies the old grades to the new pointer and frees up the
 * memory held by the old pointer.
 */
double* copy(double * ptr, int count) {
    double * returnPtr = (double *) malloc(sizeof(double)*5 + sizeof(double)*count);
    bytes += sizeof(double)*(5 + count);
    printf("Allocated %lu bytes to the heap at %p.\n", sizeof(double)*(5 + count), (void *)returnPtr);

    for (int i = 0; i < count; i++, ptr++, returnPtr++) {
        *returnPtr = *ptr;
    }
    ptr = ptr - count;
    returnPtr = returnPtr - count;
    printf("Copied %d grades from %p to %p.\n", count, (void *)ptr, (void *)returnPtr);
    //double * copyPtr = ptr;
    free(ptr);
    printf("Freed %d bytes from the heap at %p.\n", count*8, (void *)ptr);
    return returnPtr;
}

/*
 * Loops through every grade in ptr and prints whether or not
 * it is greater than or equal to the average or less than the average.
 */
void compare(const double * ptr, int count, double average) {
    for (int i = 0; i < count; i++, ptr++) {
        char * compare = (*ptr >= average) ? ">=" : "<";
        printf("%d. The grade of %.6lf is %s the average.\n", i + 1, *ptr, compare);
    }
}

/*
 * Takes the pointer to the new sequence of grades as input then computes the average of the grades.
 */
double averageGrade(const double * ptr, int count) {
    double sum = 0;
    for (int i = 0; i < count; i++, ptr++) {
        //printf("--%lf--\n", *ptr);
        sum += *ptr;
    }
    return (sum / count);
}
