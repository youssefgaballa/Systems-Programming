#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Executes commands to the left of -pipe
 * and pipes the output of the command to the write end of the pipe.
 */
void childCode(int pipefd[2], char * args[]);

/*
 * Waits for the child to finish executing, reads from the read end of the pipe,
 * then executes commands to the right of -pipe.
 */
void parentCode(int pipefd[2], char * args[]);

/*
 * Debug function to print the array passed to execvp.
 */
void printArray(char * array[]);

/*
 * Converts the command line arguments to 2 arrays, one which is passed to execvp
 * for the child process, other for the parent process.
 * Forks the current process and executes commands to the left of -pipe in the child,
 * pipes its output to the parent process, then executes commands to the right of -pipe in the parent.
 */
int main(int argc, char * argv[]) {
    // Gets the command arguments for the child process and puts them in an array
    int childSize = 0;
    for (; (childSize < argc) && (strcmp("-pipe", argv[childSize]) != 0); childSize++) {
    }
    char * childArgs[childSize];
    for (int i = 0, index = 1; (index < argc) && (strcmp("-pipe", argv[index]) != 0); i++, index++) {
        childArgs[i] = argv[index];
    }
    childArgs[childSize - 1] = NULL;
    // Gets the command arguments for the parent process and puts them in an array
    int parentSize = argc - childSize;
    int index = childSize + 1;
    char * parentArgs[parentSize];
    for (int i = 0; (index < argc); i++,index++) {
        parentArgs[i] = argv[index];
    }
    parentArgs[parentSize - 1] = NULL;

    //printArray(childArgs);
    //printArray(parentArgs);

    int pipefd[2]; // hold file descriptors for a pipe system call
    int p = pipe(pipefd);  // pipe and store pipe file descriptors in pipefd

    if (p < 0) {
        printf("Pipe failed\n");

    } else {
        int pid = fork();
        if (pid < 0) {
            printf("Fork failed\n");
        } else {
            if (pid == 0) { // child process
                childCode(pipefd, childArgs);
            } else { // parent process
                parentCode(pipefd, parentArgs);
            }
        }
    }

    return 0;
}

void childCode(int pipefd[2], char * args[]){
  // child does not need the read end of the pipe
  close(pipefd[0]);

  // replace child's standard output fd (1) with the pipe's write end
  dup2(pipefd[1], 1);

  //execute code to the left of -pipe
  execvp(args[0], args);
}

void parentCode(int pipefd[2], char * args[]){
  // parent does not need the write end of the pipe
  close(pipefd[1]);

  // replace parents's standard input fd (0) with the pipe's read end
  dup2(pipefd[0], 0);

  int status;
  // parent waits for child to complete
  wait(&status);

  //execute code to the right of -pipe
  execvp(args[0], args);
}

//debug function
void printArray(char * array[]) {
    printf("{");
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s, ", array[i]);
    }
    printf("NULL");
    printf("}\n");
}
