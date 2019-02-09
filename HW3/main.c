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
    pid_t childPid;
    int total = 0;

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

    case 0: // Child Process
        close(fd1[0]);
        printf("Starting child process (PID = %i)\n", childPid);
        char *answer = (char *)malloc(80);
        char answers[200];
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
                write(fd1[1], answers, strlen(answers) + 1);
                printf("Exiting child process...\n");
            }
            printf("\n input: %s\n", answer);
        } while (val != -1);

        close(fd2[0]);

        exit(0);

    default: // Parent Process
        wait(&status);
        close(fd1[1]);
        read(fd1[0], buf, strlen(buf) + 1);

        int temp = atoi(buf);

        if (temp != -1)
        {
            total += temp;
        }

        printf("Total = %i.\n", total);
    }
    printf("Exiting pid %i\n", getpid());

    return 0;
}
