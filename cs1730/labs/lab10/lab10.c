#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int status;
    int ppid = getpid();
    printf("The parent's PID is %d.\n", ppid);
    printf("The parent is now forking.\n");
    int rv = fork();
    if (rv < 0) {
        printf("The call to fork failed.\n");
        exit(0);
    }

    if (rv == 0) {
        int chpid = getpid();
        printf("The child's PID is %d.\n", chpid);
        char * newargv2[] = {"/user/bin/ps", NULL};
        printf("The child is executing ps.\n");
        int rv2 = execve("/usr/bin/ps", newargv2, NULL);
        if (rv2 < 0) {
            printf("execve for ps failed.\n");
            exit(0);
        }

    } else {
        int waitv = wait(&status);
        if (waitv < 0) {
            printf("Wait failed.\n");
            exit(0);
        }
        printf("The parent waited patiently for its child to complete.\n");
        printf("The parent is executing ./countdown.out %d.\n", atoi(argv[1]));
        char * newargv1[] = {"./countdown.out", argv[1], NULL};
        //char * newenviron[] = {NULL};
        char * fileName = "./countdown.out";

        int rv1 = execve(fileName, newargv1, NULL);
        if (rv1 < 0) {
            printf("execve for countdown failed.\n");
            exit(0);
        }

    }


}
