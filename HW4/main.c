#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *world();
void *hello();
void *exclamation();

int main(int argc, char *argv[])
{

    pthread_t thread[2];

    pthread_create(&thread[0], NULL, world, NULL);
    pthread_create(&thread[1], NULL, hello, NULL);
    pthread_create(&thread[2], NULL, exclamation, NULL);

    for (int j = 0; j < 3; j++)
    {
        pthread_join(thread[j], NULL);
    }

    printf("\n");

    return 0;
}

void *world()
{
    usleep(400);
    printf("world");
}

void *hello()
{
    printf("Hello ");
}

void *exclamation()
{
    usleep(600);
    printf("!");
}
