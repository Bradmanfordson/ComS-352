#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <iostream>
using namespace std;

int count = 0;

int main(void)
{

    int fd1[2];
    int fd2[2];
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

    if ((childPid = fork()) < 0)
    {

        printf("Failed to fork process 1.\n");
        exit(-1);
    }
    else if (childPid == 0)
    {
        // Child Process
        close(fd1[0]); // close reading of the first pipe so we can write input to parent
        char input[4];
        int val;
        int count = 0;

        do
        {
            count++;
            printf("Enter: ");
            cin >> input;
            if ((val = atoi(input)) == 0 || val > 255)
            {
                printf("Invalid input, enter an integer between 1 and 255, or -1 to exit.\n");
            }
            else
            {
                write(fd1[1], input, strlen(input) + 1);
            }
        } while (val != -1);

        close(fd2[1]);
        read(fd2[0], input, strlen(input) + 1);
        total += atoi(input);
        printf("Child received: %i\n", atoi(input));

        printf("Total = %i\n", total);
    }
    else
    {
        // Parent Process

        string test[100];
        close(fd1[1]); // close writing of first pipe so we can read user input from child
        read(fd1[0], buf, strlen(buf) + 1);
        close(fd1[0]);

        test[count] = atoi(buf);

        printf("Parent recieved: %i\n", atoi(buf));

        printf("Sending back to child to print\n");
        close(fd2[0]);
        write(fd2[1], test, 200);
    }

    return 0;
}
