// Author: Allen Bradley Roberts
// Date: April 26, 2019
// Course: Com S 352 - Operating Systems

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    //TODO ADD CLOCK
    char *fileIn = malloc(100);
    char *fileOut = malloc(100);

    printf("Input full path of file to read: ");
    scanf("%s", fileIn);

    printf("Input full path of file to write: ");
    scanf("%s", fileOut);

    clock_t start = clock();

    FILE *testIn, *testOut;

    if ((testIn = fopen(fileIn, "r")) == NULL)
    {
        printf("An error occured while trying to open: %s.\n", fileIn);
        printf("Make sure to give the full path of the file.\n");
        return -1;
    }
    if ((testOut = fopen(fileOut, "w")) == NULL)
    {
        printf("An error occured while trying to open: %s.\n", fileOut);
        printf("Make sure to give the full path of the file.\n");
        return -1;
    }

    char value;
    while (fread(&value, 1, 1, testIn) != 0)
    {
        if (value < 123 && value > 96) // if value is stricktly a lower case character
        {
            value = value - 32;
        }

        fwrite(&value, 1, 1, testOut);
    }

    fclose(testIn);
    fclose(testOut);

    clock_t stop = clock();

    float totalTime = stop - start;
    printf("Execution time: %f\n", totalTime);

    return 0;
}
