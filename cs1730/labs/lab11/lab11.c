#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/*
 * This signal handler for SIGFPE prints the sum
 * and exits the program.
 */
void handleSIGFPE(int signum);

/*
 * This signal handler for SIGUSR1 prints the sum
 * and exits the program.
 */
void handleSIGUSR1(int signum);

/*
 * This signal handler for SIGUSR2 prints the sum
 * and exits the program.
 */
void handleSIGUSR2(int signum);

// Denotes the sum of values read from stdin
double sum = 0;

/*
 * Creates the signal handlers, reads from standard input and
 * adds the doubles to sum, then sleeps after stdin is flushed
 * which only occurs at end of a file redirection.
 */
int main(int argc, char * argv[]) {

    signal(SIGFPE, handleSIGFPE); //8
    signal(SIGUSR1, handleSIGUSR1); //8
    signal(SIGUSR2, handleSIGUSR2); //8
    long int pid = getpid();
    printf("Program started with pid = %ld.\n", pid);
    printf("Enter a list of doubles to sum, \n");
    printf("and to end the program, \n");
    printf("run one of the following Unix commands: \n");
    printf(" kill -8 %ld\n", pid);
    printf(" kill -10 %ld\n", pid);
    printf(" kill -12 %ld\n", pid);

    char * buffer = NULL;
    size_t length = 0;
    ssize_t size;

    double num;
    while ((size = getline(&buffer, &length, stdin)) > 0) {
        //printf("size: %ld\n", size);
        if ((sscanf(buffer, "%lf", &num)) > 0) {
            //printf("num: %lf\n", num);
            sum += num;
        } else {
            printf("Error: please input a numeric value.\n");
        }
    }
    sleep(60);
    printf("The sum is %lf.\n", sum);
    printf("Program ended after sleeping for 60 seconds.\n");
    return 0;
}


void handleSIGFPE(int signum) { //SIGFPE = 8
    long int pid = getpid();
    printf("The sum is %lf.\n", sum);
    printf("Program ended by handling the signal from kill -8 %ld.\n", pid);
    exit(signum);
}

void handleSIGUSR1(int signum) { // SIGUSR1 = 10
    long int pid = getpid();
    printf("The sum is %lf.\n", sum);
    printf("Program ended by handling the signal from kill -10 %ld.\n", pid);
    exit(signum);
}


void handleSIGUSR2(int signum) { //SIGUSR2 = 12
    long int pid = getpid();
    printf("The sum is %lf.\n", sum);
    printf("Program ended by handling the signal from kill -12 %ld.\n", pid);
    exit(signum);
}
