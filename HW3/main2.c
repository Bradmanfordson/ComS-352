#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void ChildProcess(char[], char[]);

pid_t pid1, pid2, pid;
int status, i;
char buf[100];

int main(void)
{

    int fd1[2];
    int fd2[2];
    int total = 0;

    pid_t childPid;

    char input_str[100];
    char buf[100];

    if (pipe(fd1) == -1)
    {
        printf("Pipe error.\n");
        return -1;
    }
    if (pipe(fd2) == -1)
    {
        printf("Pipe error.\n");
        return -1;
    }

    switch (childPid = fork())
    {
    case -1: // Fork Failed
        printf("Failed to fork process 1.\n");
        exit(-1);

    case 0:            // Child Process
        close(fd1[0]); // close reading of the first pipe so we can write input to parent

    default:           // Parent Process
        close(fd1[1]); // close writing of first pipe so we can read user input from child
    }

    return 0;
}
