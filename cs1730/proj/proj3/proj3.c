#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Writes characters in fd1 that are different from fd2
 * into a file called differencesFoundInFile1.txt.
 * Implemented using buffers of size 1.
 * This function is timed using two calls to gettimeofday().
 */
void step1(int fd1, int fd2);

/*
 * Writes characters in fd2 that are different from fd1
 * into a file called differencesFoundInFile2.txt.
 * Implemented using buffers that are the size of the files.
 * This function is timed using two calls to gettimeofday().
 */
void step2(int fd1, int fd2);

/*
 * Converts a time represented with integers values of
 * sec and usec (microsecond) to a double in milliseconds.
 */
double timeToDouble(long int sec, long int usec);

/*
 * Handle exceptions that can occur in main function such
 * as file cannot be opened for reading or writing, and
 * incorrect number of command line arguments.
 */
void handleExceptions(int argc, int fd1, int fd2);

/*
 * Processes the command line arguments to open
 * two files and read their contents, and calling
 * the functions step1 and step2.
 */
int main(int argc, char * argv[]) {
    int fd1 = -1;
    int fd2 = -1;

    char * path1 = argv[1];
    char * path2 = argv[2];

    fd1 = open(path1, O_RDONLY);
    fd2 = open(path2, O_RDONLY);
    // error handling function
    handleExceptions(argc, fd1, fd2);

    step1(fd1, fd2);
    /*
    Cant use lseek b/c it isnt a allowed IO call
    int seek1 = lseek(fd1, 0, SEEK_SET);
    int seek2 = lseek(fd2, 0, SEEK_SET);

    if ((seek1 < 0) || (seek2 < 0)) {
        printf("Unable to seek a file.\n");
        exit(0);
    }
    We'll use Open instead
    */
    close(fd1);
    close(fd2);
    int fd3 = -1;
    int fd4 = -1;
    fd3 = open(path1, O_RDONLY);
    fd4 = open(path2, O_RDONLY);
    handleExceptions(argc, fd3, fd4);
    step2(fd1, fd2);
    close(fd1);
    close(fd2);
    return 0;
}

void step1(int fd1, int fd2) {
    struct timeval timeVal;
    int return0 = gettimeofday(&timeVal, NULL);
    if (return0 < 0) {
        printf("Unable to get the time.\n");
        exit(0);
    }
    double time1 = timeToDouble(timeVal.tv_sec, timeVal.tv_usec);
    //printf("- %lf -\n", time1);

    int size = 2;
    char * buf1 = (char *) malloc(sizeof(char) * size);
    buf1[1] = '\0';
    char * buf2 = (char *) malloc(sizeof(char) * size);
    buf1[2] = '\0';
    int fdw = open("differencesFoundInFile1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    int status1 = read(fd1,buf1,1);;
    int status2 = read(fd2,buf2,1);;
    while ((status1 > 0) && (status2 > 0)) {
        if (buf1[0] != buf2[0]) {
            write(fdw, buf1, 1);
        }
        status1 = read(fd1,buf1,1);
        status2 = read(fd2,buf2,1);
    }
    while (status1 > 0) {
        write(fdw, buf1,1);
        status1 = read(fd1, buf1,1);
    }

    close(fdw);
    free(buf1);
    free(buf2);

    int return3 = gettimeofday(&timeVal, NULL);
    if (return3 < 0) {
        printf("Unable to get the time.\n");
        exit(0);
    }
    double time2 = timeToDouble(timeVal.tv_sec, timeVal.tv_usec);
    //printf("- %lf -\n", time2);
    double timeDiff = (time2 - time1) * 1000;
    printf("Step 1 took %lf milliseconds\n", timeDiff);
}

 double timeToDouble(long int sec, long int usec) {
    double result = (double) sec;
    double microseconds = (double) usec;
    double base = 1.0E-6;
    microseconds = microseconds * base;
    result += microseconds;
    return result;
}

void step2(int fd1, int fd2) {

    struct timeval timeVal;
    int return0 = gettimeofday(&timeVal, NULL);
    if (return0 < 0) {
        printf("Unable to get the time.\n");
        exit(0);
    }
    double time1 = timeToDouble(timeVal.tv_sec, timeVal.tv_usec);

    struct stat fileinfo1;
    struct stat fileinfo2;
    //printf("- %lf -\n", time1);

    int return1 = fstat(fd1, &fileinfo1);
    if (return1 == -1) {
        printf("Unable to stat file 1\n");
        exit(0);
    }
    int return2 = fstat(fd2, &fileinfo2);
    if (return2 == -1) {
        printf("Unable to stat file 2\n");
        exit(0);
    }


    char * file1Data = (char *) malloc(sizeof(char) * ((int)fileinfo1.st_size + 1) );
    file1Data[(int)fileinfo1.st_size] = '\0';
    //printf("-%ld-\n", fileinfo1.st_size);
    //printf("fileinfo1.off_t %d\n", (int)fileinfo1.st_size);
    char * file2Data = (char *) malloc(sizeof(char) * ((int)fileinfo2.st_size + 1));
    //printf("-%ld-\n", fileinfo2.st_size);
    file2Data[(int)fileinfo2.st_size] = '\0';
    //printf("fileinfo2.off_t %d\n", (int)fileinfo2.st_size);
    char * differences = (char *) malloc(sizeof(char) * ((int)fileinfo2.st_size + 1));
    //differences[(int)fileinfo2.st_size - 1] = '\0';

    int bytes1 = read(fd1, file1Data, sizeof(char) * (int)fileinfo1.st_size);
    //printf("bytes1: %d\n", bytes1);
    int bytes2 = read(fd2, file2Data, sizeof(char) * (int)fileinfo2.st_size);
    //printf("bytes2: %d\n", bytes2);
    if ((bytes1 < 0) || (bytes2 < 0)) {
        printf("There was an error reading a file.\n");
        exit(0);
    }
    //printf("bytes2: %d\n", bytes2);
    int size = 0;
    for (int i = 0; file2Data[i] != '\0'; i++) {
        if (file1Data[i] != file2Data[i]) {
            differences[size] = file2Data[i];
            size++;
        }
    }

    differences[size] = '\0';
    //printf("- %s -\n", differences);
    int fdw = open("differencesFoundInFile2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fdw < 0) {
        printf("There was an error opening a file.\n");
        exit(0);
    }
    int bytes3 = write(fdw, differences, sizeof(char) * size);
    if (bytes3 < 0) {
        printf("There was an error writing to a file.\n");
        exit(0);
    }
    //printf("b3: %d\n", bytes3);

    free(file1Data);
    free(file2Data);
    free(differences);

    int return3 = gettimeofday(&timeVal, NULL);
    if (return3 < 0) {
        printf("Unable to get the time.\n");
        exit(0);
    }
    double time2 = timeToDouble(timeVal.tv_sec, timeVal.tv_usec);
    //printf("- %lf -\n", time2);
    double timeDiff = (time2 - time1) * 1000;
    printf("Step 2 took %lf milliseconds\n", timeDiff);
}

void handleExceptions(int argc, int fd1, int fd2) {
    if(argc != 3){
        printf("Usage: ./proj3.out <file1> <file2>\n");
        exit(0);
    }

    if(fd1 < 0){
        printf("There was an error reading a file.");
        exit(0);
    }

    if(fd2 < 0){
        printf("There was an error reading a file.");
        exit(0);
    }
}
