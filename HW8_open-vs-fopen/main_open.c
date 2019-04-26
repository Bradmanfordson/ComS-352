#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char *f = "test.txt"; // input file
    char *o = "caps.txt"; // output file

    int fd = open(f, O_RDONLY);

    void *value;
    while (read(fd, value, 1) == 0)
    {
        printf("%s\n", value);
    }

    close(fd);
    return 0;
}
