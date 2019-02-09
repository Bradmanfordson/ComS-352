#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <iostream>
using namespace std;

void ChildProcess(char[], char[]);

pid_t pid1, pid2, pid;
int status, i;
char buf[100];

int main(void)
{

    int fd1[2];
    int fd2[2];
    pid_t childPid;
    int total = 0;

    string buf[100];

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

    if ((childPid = fork()) == -1)
    { // Fork Failed
        printf("Failed to fork process 1.\n");
        exit(-1);
    }

    else if (childPid == 0)
    {

        close(fd1[0]);
        printf("Starting child process (PID = %i)\n", childPid);
        char *answer = (char *)malloc(80);
        string answers[200];
        int val;
        int counter;
        do
        {
            counter += 1;
            printf("Enter an integer between 1 and 255, enter -1 to exit:");
            scanf("%s", answer);
            if ((val = atoi(answer)) == 0 || val > 255)
            {
                printf("Invalid input, enter an integer between 1 and 255, or -1 to exit.\n");
            }
            else if (val != -1)
            {
                answers[counter] = (char)val;
                // printf("answers: %c\n", answers[counter]);
                //pipe to parent process
            }
            else
            {
                write(fd1[1], answers, sizeof(answers));
                printf("Exiting child process...\n");
            }
            printf("\n input: %s\n", answer);
        } while (val != -1);

        close(fd2[0]);

        exit(0);
    }

    else
    {
        // Parent Process
        close(fd1[1]);
        read(fd1[0], buf, sizeof(buf));

        for (string x : buf)
        {
            total += stoi(x);
        }

        printf("Total = %i.\n", total);
    }

    printf("Exiting pid %i\n", getpid());

    return 0;
}
