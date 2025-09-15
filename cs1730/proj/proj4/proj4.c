#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>



/*
 * The struct grid_t contains a pointer p to a 2D array of
 * unsigned chars with n rows and n columns stored on
 * the heap of this process. Once this is initialized properly,
 * p[i][j] should be a valid unsigned char for all i = 0..(n-1)
 * and j = 0..(n-1).
 * Do not alter this typedef or struct in any way.
 */
typedef struct grid_t {
  unsigned int n;
  unsigned char ** p;
} grid;

/*
 * This struct is used to pass multiple arguments
 * to the pthread_create call.
 */
struct pthread_create_args {
    int t;
    unsigned long s;
    grid * output;
    grid * input;
};

/*
 * Initialize g based on fileName, where fileName
 * is a name of file in the present working directory
 * that contains a valid n-by-n grid of digits, where each
 * digit in the grid is between 1 and 9 (inclusive).
 * Do not alter this function prototype in any way.
 */
void initializeGrid(grid * g, char * fileName) {

    int fd = open(fileName, O_RDONLY);
    if (fd < 0) {
        printf("There was an error opening a file.\n");
        exit(0);
    }

    // we need to get the length of the rows/columns to malloc correctly
    char * buffer = (char *) malloc(sizeof(char) * 2);
    buffer[1] = '\0';
    unsigned int size = 0;
    int status = read(fd, buffer, 1);
    while((buffer[0] != 10) && (status > 0)) { // 10 = '\n'
        status = read(fd, buffer, 1);
        size++;
    }
    if (status < 0) {
        printf("There was an error reading a file.\n");
        exit(0);
    }
    //printf("Size: %hd\n", size);
    int status1 = lseek(fd, 0, SEEK_SET);
    if (status1 < 0) {
        printf("There was an error lseeking a file.\n");
        exit(0);
    }
    g->n = size;
    g->p = (unsigned char **) malloc(sizeof(unsigned char **) * size); // malloc the rows
    status = read(fd, buffer, 1);
    for (int r = 0; r < g->n; r++) {
        *((g->p) + r) = (unsigned char *) malloc(sizeof(unsigned char *) * (size + 1));
        for (int c = 0; c < g->n; c++) {
            if (status > 0) {
                g->p[r][c] = buffer[0];
            }
            status = read(fd, buffer, 1);
            if (buffer[0] == 10) {// 10 = '\n'

                status = read(fd, buffer, 1);
            }

        }

        g->p[r][g->n]='\0';

    }

    free(buffer);
    close(fd);
}

/*
 * Computes the diagonal sum for input[r][c] going in the bottom left direction.
 * If the sum is equal to s it copies over each element in that diagonal
 * to the coorresponding rows, columns in output.
 */
void computeDiag_toBL(grid * input, unsigned long s, grid * output, int r, int c) {
    unsigned int sum = 0;
    // [r][c] to top left
    int row = r;
    int col = c;
    char num[2];
    num[1] = '\0';
    while ((row <= (input->n - 1)) && (col >= 0) && (sum <= s)) {
        //printf("[%d][%d]: \n", row, col);
        if (sum == s) {
            row--;
            col++;

            while ((row >= r) && (col <= c)) {
                output->p[row][col]=input->p[row][col];
                row--;
                col++;
            }
            sum++; // necessary to exit the loop
        } else if (sum < s) {
            num[0] =  input->p[row][col];
            sum += atoi(num);
            row++;
            col--;
        } else {
            // will exit loop
        }
    }
    if (sum == s) { // could happen on first row
        row--;
        col++;

        while ((row >= r) && (col <= c)) {
            output->p[row][col]=input->p[row][col];
            row--;
            col++;
        }
    }
}

/*
 * Computes the diagonal sum for input[r][c] going in the bottom right direction.
 * If the sum is equal to s it copies over each element in that diagonal
 * to the coorresponding rows, columns in output.
 */
void computeDiag_toBR(grid * input, unsigned long s, grid * output, int r, int c) {
    unsigned int sum = 0;
    // [r][c] to top left
    int row = r;
    int col = c;
    char num[2];
    num[1] = '\0';
    while ((row <= (input->n - 1)) && (col <= (input->n - 1)) && (sum <= s)) {
        //printf("[%d][%d]: \n", row, col);
        if (sum == s) {
            //printf("sum\n");
            row--;
            col--;

            while ((row >= r) && (col >= c)) {
                output->p[row][col]=input->p[row][col];
                row--;
                col--;
            }
            sum++; // necessary to exit the loop
        } else if (sum < s) {
            num[0] =  input->p[row][col];
            sum += atoi(num);
            row++;
            col++;
        } else {
            // will exit loop
        }
    }
    if (sum == s) { // could happen on first row
        row--;
        col--;

        while ((row >= r) && (col >= c)) {
            output->p[row][col]=input->p[row][col];
            row--;
            col--;
        }
    }
}

/*
 * This function is called by the second thread to compute
 * the second half of rows (if t == 2), or the second third
 * of rows (if t == 3).
 */
void * thread2_work(void * args) {
    struct pthread_create_args * pArgs = (struct pthread_create_args *) args;
    int t = pArgs->t;
    grid * input = pArgs->input;
    grid * output = pArgs->output;
    unsigned long s = pArgs->s;

    if (t == 2) {
        //printf("(output->n / %d): %hd\n", t, (output->n / t) );
        for (int r = (output->n / t); r < output->n; r++) {
            for (int c = 0; c < output->n; c++) {
                computeDiag_toBL(input, s, output, r, c);
                computeDiag_toBR(input, s, output, r, c);
            }
        }
    } else if (t == 3) {
        //printf("(output->n / %d): %hd\n", t, (output->n / t) );
        //printf("2*(output->n / %d): %hd\n", t, 2*(output->n / t) );
        for (int r = (output->n / t); r < 2 * (output->n / t); r++) {
            for (int c = 0; c < output->n; c++) {
                computeDiag_toBL(input, s, output, r, c);
                computeDiag_toBR(input, s, output, r, c);
            }
        }

    }
    return NULL;
}

/*
 * This function is called by the third thread to compute the
 * last third of rows.
 */
void * thread3_work(void * args) {
    // only invoked when t == 3 so we dont need to use that variable
    struct pthread_create_args * pArgs = (struct pthread_create_args *) args;
    //int t = pArgs->t;
    grid * input = pArgs->input;
    grid * output = pArgs->output;
    unsigned long s = pArgs->s;
    //printf("2*(output->n / 3): %hd\n", 2*(output->n / 3) );
    //printf("output->n: %hd\n", output->n );
    for (int r = 2*(output->n / 3); r < output->n; r++) {
        for (int c = 0; c < output->n; c++) {
            computeDiag_toBL(input, s, output, r, c);
            computeDiag_toBR(input, s, output, r, c);
        }
    }
    return NULL;
}

/*
 * This function will compute all diagonal sums in input that equal s using
 * t threads, where 1 <= t <= 3, and store all of the resulting
 * diagonal sums in output. Each thread should do
 * roughly (doesn't have to be exactly) (100 / t) percent of the
 * computations involved in calculating the diagonal sums.
 * This function should call (or call another one of your functions that calls)
 * pthread_create and pthread_join when 2 <= t <= 3 to create additional POSIX
 * thread(s) to compute all diagonal sums.
 * Do not alter this function prototype in any way.
 */
void diagonalSums(grid * input, unsigned long s, grid * output, int t) {
    output->n = input->n;
    output->p = (unsigned char **) malloc(sizeof(unsigned char **) * output->n);
    for (int r = 0; r < output->n; r++) {
        *((output->p) + r) = (unsigned char *) malloc(sizeof(unsigned char *) * (output->n + 1));
        for (int c = 0; c < output->n; c++) {
            output->p[r][c] = 48; //'48 = 60
        }
        output->p[r][output->n]='\0';
    }
    if (t == 1) {
        for (int r = 0; r < output->n; r++) {
            for (int c = 0; c < output->n; c++) {
                computeDiag_toBL(input, s, output, r, c);
                computeDiag_toBR(input, s, output, r, c);
            }
        }
    } else if (t == 2) {
        struct pthread_create_args pArgs;
        pArgs.input = input;
        pArgs.output = output;
        pArgs.s = s;
        pArgs.t = t;
        pthread_t pthread2;
        if (pthread_create(&pthread2, NULL, thread2_work, &pArgs) != 0) {
            fprintf(stderr, "Error creating pthread2\n");
            exit(0);
        }
        //printf("(output->n / 2): %hd\n", (output->n / 2));
        for (int r = 0; r < (output->n / 2); r++) {
            for (int c = 0; c < output->n; c++) {
                computeDiag_toBL(input, s, output, r, c);
                computeDiag_toBR(input, s, output, r, c);
            }
        }
        if(pthread_join(pthread2, NULL) != 0) {
            fprintf(stderr, "Error joining pthread2 with the first thread\n");
            exit(0);
        }
    } else if (t == 3) {
        struct pthread_create_args pArgs;
        pArgs.input = input;
        pArgs.output = output;
        pArgs.s = s;
        pArgs.t = t;
        pthread_t pthread2;
        pthread_t pthread3;
        if (pthread_create(&pthread2, NULL, thread2_work, &pArgs) != 0) {
            fprintf(stderr, "Error creating pthread2\n");
            exit(0);
        }
        if (pthread_create(&pthread3, NULL, thread3_work, &pArgs) != 0) {
            fprintf(stderr, "Error creating pthread3\n");
            exit(0);
        }
        //printf("(output->n / 3): %hd\n", (output->n / 3));
        for (int r = 0; r < (output->n / 3); r++) {
            for (int c = 0; c < output->n; c++) {
                computeDiag_toBL(input, s, output, r, c);
                computeDiag_toBR(input, s, output, r, c);
            }
        }
        if (pthread_join(pthread2, NULL) != 0) {
            fprintf(stderr, "Error joining pthread2 with the first thread\n");
            exit(0);
        }
        if (pthread_join(pthread3, NULL) != 0) {
            fprintf(stderr, "Error joining pthread3 with the first thread\n");
            exit(0);
        }
        //printf("Threads joined!\n");
    } else {
    }

}

/*
 * Write the contents of g to fileName in the present
 * working directory. If fileName exists in the present working directory,
 * then this function should overwrite the contents in fileName.
 * If fileName does not exist in the present working directory,
 * then this function should create a new file named fileName
 * and assign read and write permissions to the owner.
 * Do not alter this function prototype in any way.
 */
void writeGrid(grid * g, char * fileName) {
    int fd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        printf("There was an error opening %s.\n", fileName);
        printf("errno: %d\n", errno);
        exit(0);
    }
    char * nl = (char *) malloc(sizeof(char) * 2);
    nl[0] = '\n';
    int bytes = write(fd, *(g->p + 0), g->n);
    int bytes1 = write(fd, nl, sizeof(char)*1);
    int i = 1;
    while ((bytes > 0) && (bytes1 > 0) && (i < g->n)) {
        bytes = write(fd, *(g->p + i), g->n);
        bytes1 = write(fd, nl, sizeof(char)*1);
        i++;
    }
    if ((bytes < 0) || (bytes1 < 0)) {
        printf("There was an error writing to %s.\n", fileName);

        exit(0);
    }
    free(nl);
    close(fd);
}

/*
 * Free up all dynamically allocated memory used by g.
 * This function should be called when the program is finished using g.
 * Do not alter this function prototype in any way.
 */
void freeGrid(grid * g) {
    for (int r = 0; r < g->n; r++) {
        free(*((g->p) + r));
    }
    free(g->p);
}
