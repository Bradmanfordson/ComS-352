// Author: Allen Bradley Roberts
// Date: April 26, 2019
// Course: Com S 352 - Operating Systems

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char *fileIn = malloc(100);
    char *fileOut = malloc(100);

    printf("Input full path of file to read: ");
    scanf("%s", fileIn);

    printf("Input full path of file to write: ");
    scanf("%s", fileOut);

    clock_t start = clock();

    int inputFD, outputFD;

    if ((inputFD = open(fileIn, O_RDONLY)) == -1)
    {
        printf("An error occured while trying to open: %s.\n", fileIn);
        printf("Make sure to give the full path of the file.\n");
        return -1;
    }

    if ((outputFD = open(fileOut, O_WRONLY)) == -1)
    {
        printf("An error occured while trying to open: %s.\n", fileOut);
        printf("Make sure to give the full path of the file.\n");
        return -1;
    }

    struct stat filestat;
    stat(fileIn, &filestat);

    char value;

    while (read(inputFD, &value, 1) != 0)
    {
        if (value < 123 && value > 96) // if value is stricktly a lower case character
        {
            value = value - 32;
        }

        write(outputFD, &value, 1);
    }

    close(inputFD);
    close(outputFD);

    clock_t stop = clock();

    float totalTime = stop - start;
    printf("Execution time: %f\n", totalTime);
    return 0;
}
