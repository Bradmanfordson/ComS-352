// Allen Bradley Roberts
// Computer Science 352 - Operating Systems
// February 9, 2019

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

int main(void)
{

    int pipe1[2], pipe2[2];

    int total = 0;

    pid_t childPid;

    char buf[4];

    //create pipes
    if (pipe(pipe1) == -1)
    {
        std::cout << "Pipe1 error." << std::endl;
        exit(1);
    }
    if (pipe(pipe2) == -1)
    {
        std::cout << "Pipe2 error." << std::endl;
        exit(1);
    }

    if ((childPid = fork()) < 0) // Child process failed to start
    {

        printf("Failed to fork process.\n");
        exit(1);
    }
    else if (childPid == 0) // Child Process sucessful
    {
        int input = 0;

        while (input != -1)
        {
            std::cout << "Enter an integer between 1 and 255, enter -1 to exit: ";
            std::cin >> input;
            std::cout << std::endl;
            if (input < 255)
            {
                close(pipe1[0]);            // close reading of the first pipe so we can write input to parent
                write(pipe1[1], &input, 1); // send input to parent to be added.
            }
            else
            {
                std::cout << "Invalid input." << std::endl;
            }
        }
        close(pipe2[1]);                       // close writing of second pipe
        read(pipe2[0], &total, sizeof(total)); // read from parent to be printed
        std::cout << "Total: " << total << std::endl;
    }
    else // Parent Process
    {

        int childInput = 0;

        do
        {
            total = total + childInput;
            close(pipe1[1]);
            read(pipe1[0], &childInput, 1); // get from child to be added.
        } while (childInput != 255);

        close(pipe2[0]);
        write(pipe2[1], &total, sizeof(total)); // send back to child to be printed
    }

    return 0;
}
