#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main(void)
{

    int pipe1[2];
    int pipe2[2];
    int total = 0;

    pid_t childPid;

    char buf[4];

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
        char input[4];
        int val;

        printf("Enter: ");
        scanf("%s", input);
        if ((val = atoi(input)) == 0 || val > 255)
        {
            printf("Invalid input, enter an integer between 1 and 255, or -1 to exit.\n");
        }
        else
        {
            write(fd1[1], input, strlen(input) + 1);
        }

        close(fd2[1]);
        read(fd2[0], input, strlen(input) + 1);
        close(fd2[0]);
        total += atoi(input);
        printf("Child received: %i\n", atoi(input));

        printf("Total = %i\n", total);
        exit(0);

    default:           // Parent Process
        close(fd1[1]); // close writing of first pipe so we can read user input from child
        read(fd1[0], buf, strlen(buf) + 1);
        close(fd1[0]);

        printf("Parent recieved: %i\n", atoi(buf));

        printf("Sending back to child to print\n");
        close(fd2[0]);
        write(fd2[1], buf, strlen(buf) + 1);
    }

    return 0;
}
